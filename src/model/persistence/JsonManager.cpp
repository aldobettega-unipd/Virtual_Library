#include "JsonManager.h"
#include "../observers/JsonObserver.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>
#include <QDir>

JsonManager::JsonManager(const QString& filePath, QObject* parent)
    : QObject(parent), filePath(filePath) {}

void JsonManager::addObserver(JsonObserver* obs) {
    //aggiunge obs alla lista di puntatori agli observers se obs è valido e non è già nella lista
    if (obs && !observers.contains(obs)) observers.append(obs);
}

void JsonManager::notifyObservers() {
    // notifica tutti gli observer sulla lista observers
    for (auto* obs : observers)
        obs->onBibliotecaUpdated(bibliotecaList);
}

// Legge il file e lo traduce in QJsonArray e lo scrive su jsonArray
bool JsonManager::readJsonArray(QJsonArray& jsonArray) const {
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Il file biblioteca.json non si apre";
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "Formato Json non valido in biblioteca.json";
        return false;
    }

    jsonArray = doc.array();
    return true;
}

bool JsonManager::writeJsonArray(QJsonArray& in) const {
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Impossibile aprire biblioteca.json scrittura:";
        return false;
    }

    // da QJson array a QJson document
    QJsonDocument doc(in);
    return true;
}

QList<Biblioteca*> JsonManager::loadBibliotecaListFromJson() {
    QList<Biblioteca*> out;
    QJsonArray arr;

    // se la lettura non riesce, ritorna una lista vuota
    if (!readJsonArray(arr)) {
        qWarning() << "Lettura non riuscita";
        return out = {};
    }

    // itero il QJsonArray arr contenente i dati della mia biblioteca, per ogni elemento var ne ricava la classe (tradotta in stringa),
    // in base ad essa sceglie il corretto loader
    for (const auto& val : arr) {
        const auto obj = val.toObject();
        const auto classe = obj.value("Classe").toString();
        Biblioteca* created = nullptr;

        if (classe == "Libro")
            created = loadLibri(obj);
        // TO DO: aggiungere le classi

        else qWarning() << "Classe sconosciuta:" << classe;

        if (created)
            out.append(created);
    }

    bibliotecaList = out;
    notifyObservers();
    return out;
}

// Elenco dei vari loader

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

Biblioteca* JsonManager::loadLibri(const QJsonObject& obj) const {
    const auto b = loadBiblioteca(obj);
    const auto c = loadMediaCartaceo(obj);

    const QString autore = obj.value("autore").toString();

    return new Libro(b.titolo.toStdString(), b.annoPubblicazione.toStdString(), b.id.toStdString(),
                     b.genere.toStdString(), b.immagine.toStdString(), b.lingua.toStdString(),
                     b.copieTotali, c.numeroPagine, c.editore.toStdString(),
                     autore.toStdString(), b.copieInPrestito, c.letto);
}


//operazione di salvataggio di un oggetto Biblioteca nella lista e scrittura nel file Json
void JsonManager::saveNewObject(Biblioteca* b) {
    bibliotecaList.append(b);
    QJsonArray arr;

    if(!readJsonArray(arr)) {
        qWarning() << "Lettura di biblioteca.json non riuscita";
        return;
    }

    QJsonObject obj;
    // chiamata al giusto save che restituirà l'oggetto json da aggiungere al QJsonArray arr
    // TODO aggiungere nuove classi
    if (auto p = dynamic_cast<Libro*>(b)) {
        obj = save(p);
    } else {
        qWarning() << "[JsonManager] Tipo non supportato in saveNewObject";
        return;
    }
    arr.append(obj);

    // viene riscritta la lista con il nuovo elemento
    if (writeJsonArray(arr)) {
        qDebug() << "Json array scritto con successo";
        notifyObservers();
    } else {
        qWarning() << "Fallito nello scrivere il Json array";
    }
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

// ritorna l'oggetto Json da salvare completo
QJsonObject JsonManager::save(const Libro* libro) const {
    QJsonObject obj;
    obj["Classe"] = "Libro";
    save(static_cast<const Biblioteca*>(libro), obj);
    save(static_cast<const Media_cartaceo*>(libro), obj);

    obj["autore"] = QString::fromStdString(libro->getAutore());
    return obj;
}





void JsonManager::deleteObject(Biblioteca* biblio) {
    //
    int index = -1;
    for (int i = 0; i < bibliotecaList.size(); ++i) {
        if(bibliotecaList[i] == biblio) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        qWarning() << "L'oggetto da eliminare non è stato trovato";
        return;
    }

    // Rimuove l'elemento dalla lista e memorizzo il puntatore da deallocare
    Biblioteca* toDelete = bibliotecaList.takeAt(index);

    // Lettura del QJsonArray
    QJsonArray arr;
    if (!readJsonArray(arr)) return;

    // Rimozione dell'elemento dal QJsonArray
    if (index < arr.size()) {
        arr.removeAt(index);
        writeJsonArray(arr);
    }

    // Dealloco il puntatore e notifico gli osservatori del cambiamento
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
    if (index == -1) {
        qWarning() << "L'Oggetto da aggiornare non è stato trovato";
        return;
    }

    QJsonArray arr;
    if (!readJsonArray(arr)) return;

    QJsonObject obj;
    // dispatch del tipo di oggetto da aggiornare, viene chiamato il giusto save che ritorna il QJsonObject da aggiornare
    if (auto p = dynamic_cast<Libro*>(biblio))
        obj = save(p);
    //TODO aggiungere classi
    else {
        qWarning() << "Tipo non supportato in updateObject";
        return;
    }

    //viene sovrascritto il vecchio elemento con quello aggiornato, riscritto l'array e notificati gli observers dell'operazione
    arr[index] = obj;
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




