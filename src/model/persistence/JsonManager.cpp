#include "JsonManager.h"
#include "../observers/JsonObserver.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>

JsonManager::JsonManager(const QString& filePath, QObject* parent)
    : QObject(parent), filePath(filePath) {}

void JsonManager::addObserver(JsonObserver* obs) {
    //aggiunge obs alla lista di puntatori agli observers se obs è valido e non è già nella lista
    if (obs && !observers.contains(obs)) observers.append(obs);
}

void JsonManager::notifyObservers() {
    for (auto* obs : observers)
        obs->onBibliotecaUpdated(bibliotecaList);
}

bool JsonManager::readJsonArray(QJsonArray& out) const {
    qDebug() << "Loading JSON from:" << filePath;
    QFile file(filePath);

    if (!file.exists()) {
        qDebug() << "[JsonManager] File non esistente, creo array vuoto";
        out = QJsonArray();
        return true;
    }

    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "[JsonManager] Impossibile aprire in lettura:" << filePath;
        return false;
    }
    QByteArray data = file.readAll();
    file.close();

    // Se il file è vuoto, restituisci array vuoto
    if (data.isEmpty()) {
        qDebug() << "[JsonManager] File vuoto, restituisco array vuoto";
        out = QJsonArray();
        return true;
    }

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "[JsonManager] Documento non è un array JSON";
        return false;
    }

    out = doc.array();
    return true;
}

bool JsonManager::writeJsonArray(QJsonArray& in) const {
    // Assicurati che la directory esista
    QFileInfo fileInfo(filePath);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "[JsonManager] Impossibile creare directory:" << dir.path();
            return false;
        }
    }

    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "[JsonManager] Impossibile aprire in scrittura:" << filePath;
        return false;
    }

    QJsonDocument doc(in);
    const auto ok = file.write(doc.toJson()) != -1;
    file.close();

    if (!ok) {
        qWarning() << "[JsonManager] Scrittura fallita";
    } else {
        qDebug() << "[JsonManager] File scritto correttamente:" << filePath;
    }

    return ok;
}

QList<Biblioteca*> JsonManager::loadBibliotecaListFromJson() {
    QList<Biblioteca*> out;
    QJsonArray arr;
    if (!readJsonArray(arr)) {
        bibliotecaList = {};
        notifyObservers();
        return out;
    }

    for (const auto& val : arr) {
        const auto obj = val.toObject();
        const auto cls = obj.value("Classe").toString();
        Biblioteca* created = nullptr;
        if (cls == "Libro") created = loadLibri(obj);
        else qWarning() << "[JsonManager] Classe sconosciuta:" << cls;

        if (created) out.append(created);
    }
    bibliotecaList = out;
    notifyObservers();
    return out;
}

JsonManager::BibliotecaData JsonManager::loadBiblioteca(const QJsonObject& obj) const {
    BibliotecaData b;
    b.titolo = obj.value("titolo").toString();
    b.annoPubblicazione = obj.value("annoPubblicazione").toString();
    b.id = obj.value("id").toString();
    b.genere = obj.value("genere").toString();
    b.immagine = obj.value("immagine").toString();
    b.lingua = obj.value("lingua").toString();
    b.copieTotali = obj.value("copieTotali").toInt();
    b.copieInPrestito = obj.value("copieInPrestito").toInt();
    b.disponibile = obj.value("disponibile").toBool();
    return b;
}


JsonManager::MediaCartaceoData JsonManager::loadMediaCartaceo(const QJsonObject& obj) const {
    MediaCartaceoData m;
    m.numeroPagine = obj.value("numeroPagine").toInt();
    m.editore = obj.value("editore").toString();
    m.letto = obj.value("letto").toBool();
    return m;
}

//crea un oggetto libro dall'oggetto Json
Biblioteca* JsonManager::loadLibri(const QJsonObject& obj) const {
    const auto b = loadBiblioteca(obj);
    const auto c = loadMediaCartaceo(obj);

    const QString autore = obj.value("autore").toString();

    return new Libro(b.titolo.toStdString(), b.annoPubblicazione.toStdString(), b.id.toStdString(),
                     b.genere.toStdString(), b.immagine.toStdString(), b.lingua.toStdString(),
                     b.copieTotali, c.numeroPagine, c.editore.toStdString(),
                     autore.toStdString(), b.copieInPrestito, c.letto);
}

//metodi dispatch di salvataggio: da oggetto Biblioteca ad oggetto Json
void JsonManager::save(const Biblioteca* b, QJsonObject& obj) const {
    obj["titolo"] = QString::fromStdString(b->getTitolo());
    obj["annoPubblicazione"] = QString::fromStdString(b->getAnnoPubblicazione());
    obj["id"] = QString::fromStdString(b->getId());
    obj["genere"] = QString::fromStdString(b->getGenere());
    obj["immagine"] = QString::fromStdString(b->getImmagine());
    obj["lingua"] = QString::fromStdString(b->getLingua());
    obj["copieTotali"] = b->getCopieTotali();
    obj["copieInPrestito"] = b->getCopieInPrestito();
}

void JsonManager::save(const Media_cartaceo* c, QJsonObject& obj) const {
    obj["numeroPagine"] = c->getNumeroPagine();
    obj["editore"] = QString::fromStdString(c->getEditore());
    obj["letto"] = c->getLetto();
}

QJsonObject JsonManager::save(const Libro* libro) const {
    QJsonObject o; o["Classe"] = "Libro";
    save(static_cast<const Biblioteca*>(libro), o);
    save(static_cast<const Media_cartaceo*>(libro), o);

    o["autore"] = QString::fromStdString(libro->getAutore());
    return o;
}


//operazione di salvataggio di un oggetto Biblioteca nella lista Json
void JsonManager::saveNewObject(Biblioteca* b) {
    qDebug() << "saveNewObject called for:" << QString::fromStdString(b->getTitolo());

    bibliotecaList.append(b);
    qDebug() << "Added to bibliotecaList, now size:" << bibliotecaList.size();

    QJsonArray arr;
    if(!readJsonArray(arr)) {
        qWarning() << "Failed to read JSON array";
        return;
    }

    QJsonObject obj;
    if (auto p = dynamic_cast<Libro*>(b)) {
        obj = save(p);
        qDebug() << "Created JSON object for Libro";
    } else {
        qWarning() << "[JsonManager] Tipo non supportato in saveNewObject";
        return;
    }

    arr.append(obj);
    qDebug() << "Added object to JSON array, new size:" << arr.size();

    if (writeJsonArray(arr)) {
        qDebug() << "JSON array written successfully";
        notifyObservers();
    } else {
        qWarning() << "Failed to write JSON array";
    }
}

void JsonManager::deleteObject(Biblioteca* biblio) {
    // Find the object to delete
    int index = -1;
    for (int i = 0; i < bibliotecaList.size(); ++i) {
        if(bibliotecaList[i] == biblio) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        qWarning() << "[JsonManager] Object not found for deletion";
        return;
    }

    // Remove from memory list
    Biblioteca* toDelete = bibliotecaList.takeAt(index);

    // Update JSON file
    QJsonArray arr;
    if (!readJsonArray(arr)) return;

    if (index < arr.size()) {
        arr.removeAt(index);
        writeJsonArray(arr);
    }

    // Delete the object from memory
    delete toDelete;
    notifyObservers();
}

void JsonManager::updateObject(Biblioteca* biblio) {
    int index = -1;
    for (int i = 0; i < bibliotecaList.size(); ++i) {
        if (bibliotecaList[i] == biblio) {
            index = i;
            break;
        }
    }
    QJsonArray arr;
    if (!readJsonArray(arr)) return;
    if (index >= arr.size()) {
        qWarning() << "[JsonManager] Indice fuori range dal file";
        return;
    }

    QJsonObject o;
    if (auto p = dynamic_cast<Libro*>(biblio)) o = save(p);
    else {
        qWarning() << "[JsonManager] Tipo non supportato in updateObject";
        return;
    }
    arr[index] = o;
    writeJsonArray(arr);
    notifyObservers();
}

void JsonManager::savePrenota(Biblioteca* biblio) {
    // Aggiorna solo Disponibile/Copie dell'occorrenza specifica
    int occToSkip = 0;
    for (auto* it : bibliotecaList) {
        if (it == biblio) break;
        if (it->getTitolo() == biblio->getTitolo()) ++occToSkip;
    }


    QJsonArray arr; if (!readJsonArray(arr)) return;
    QJsonArray updated;
    int occ = 0; bool done = false;
    for (const auto& v : arr) {
        auto o = v.toObject();
        if (!done && o.value("Titolo").toString() == QString::fromStdString(biblio->getTitolo())) {
            if (occ == occToSkip) {
                o["disponibile"] = biblio->getDisponibilità();
                o["copieInPrestito"] = biblio->getCopieInPrestito();
                done = true;
            }
            ++occ;
        }
        updated.append(o);
    }
    if (done) writeJsonArray(updated);
    notifyObservers();
}

void JsonManager::saveLetto(Media_cartaceo* cartaceo) {
    int occToSkip = 0;
    for (auto* it : bibliotecaList) {
        if (it == cartaceo) break;
        if (it->getTitolo() == cartaceo->getTitolo()) ++occToSkip;
    }


    QJsonArray arr; if (!readJsonArray(arr)) return;
    QJsonArray updated; int occ = 0; bool done = false;
    for (const auto& v : arr) {
        auto o = v.toObject();
        if (!done && o.value("Titolo").toString() == QString::fromStdString(cartaceo->getTitolo())) {
            if (occ == occToSkip) { o["Letto"] = cartaceo->getLetto(); done = true; }
            ++occ;
        }
        updated.append(o);
    }
    if (done) writeJsonArray(updated);
    notifyObservers();
}




