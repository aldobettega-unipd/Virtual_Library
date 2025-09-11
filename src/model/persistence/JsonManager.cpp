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

QString JsonManager::getFilePath() const {
    return filePath;
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
    file.write(doc.toJson(QJsonDocument::Indented));
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

        if (classe == "Media_video") {
            created = loadMediaVideo(obj);
        } else if (classe == "Cd") {
            created = loadCd(obj);
        } else if (classe == "Periodico") {
            created = loadPeriodici(obj);
        } else if (classe == "Libro") {
            created = loadLibri(obj);
        } else qWarning() << "Classe sconosciuta:" << classe;

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

JsonManager::MultimediaData JsonManager::loadMultimedia(const QJsonObject& obj) const {
    MultimediaData m;
    m.supportoTecnologico = obj.value("supportoTecnologico").toString();
    m.casaDiProduzione = obj.value("casaDiProduzione").toString();
    m.durata = obj.value("durata").toInt();
    return m;
}

JsonManager::MediaCartaceoData JsonManager::loadMediaCartaceo(const QJsonObject& obj) const {
    MediaCartaceoData m;
    m.numeroPagine = obj.value("numeroPagine").toInt();
    m.editore = obj.value("editore").toString();
    m.letto = obj.value("letto").toBool();
    return m;
}

Biblioteca* JsonManager::loadMediaVideo(const QJsonObject& obj) const {
    const auto b = loadBiblioteca(obj);
    const auto m = loadMultimedia(obj);

    MediaVideoData v;

    v.regista = obj.value("regista").toString();
    v.guardato = obj.value("guardato").toBool();

    return new Media_video(b.titolo.toStdString(), b.annoPubblicazione.toStdString(), b.id.toStdString(),
                           b.genere.toStdString(), b.immagine.toStdString(), b.lingua.toStdString(),
                           b.copieTotali, m.supportoTecnologico.toStdString(), m.casaDiProduzione.toStdString(),
                           m.durata, v.regista.toStdString(), v.guardato, b.copieInPrestito
                           );
}

JsonManager::MediaAudioData JsonManager::loadMediaAudio(const QJsonObject& obj) const {
    MediaAudioData a;
    a.ascoltato = obj.value("ascoltato").toBool();
    return a;
}


Biblioteca* JsonManager::loadPeriodici(const QJsonObject& obj) const {
    const auto b = loadBiblioteca(obj);
    const auto c = loadMediaCartaceo(obj);

    PeriodicoData p;

    QString periodoStr = obj.value("periodo").toString();
    QString diffusioneStr = obj.value("diffusione").toString();

    p.periodo = Periodico::stringToPeriodo(periodoStr.toStdString());
    p.diffusione = Periodico::stringToDiffusione(diffusioneStr.toStdString());
    p.numero_articoli = obj.value("numeroArticoli").toInt();
    p.data = obj.value("data").toString();

    return new Periodico(b.titolo.toStdString(), b.annoPubblicazione.toStdString(), b.id.toStdString(),
                         b.genere.toStdString(), b.immagine.toStdString(), b.lingua.toStdString(),
                         b.copieTotali, c.numeroPagine, c.editore.toStdString(),
                         p.periodo, p.diffusione, p.numero_articoli, p.data.toStdString(), b.copieInPrestito, c.letto);

}


Biblioteca* JsonManager::loadLibri(const QJsonObject& obj) const {
    const auto b = loadBiblioteca(obj);
    const auto c = loadMediaCartaceo(obj);

    LibroData l;
    l.autore = obj.value("autore").toString();

    return new Libro(b.titolo.toStdString(), b.annoPubblicazione.toStdString(), b.id.toStdString(),
                     b.genere.toStdString(), b.immagine.toStdString(), b.lingua.toStdString(),
                     b.copieTotali, c.numeroPagine, c.editore.toStdString(),
                     l.autore.toStdString(), b.copieInPrestito, c.letto);
}

Biblioteca* JsonManager::loadCd(const QJsonObject& obj) const {
    const auto b = loadBiblioteca(obj);
    const auto m = loadMultimedia(obj);
    const auto a = loadMediaAudio(obj);

    CdData c;
    c.artista = obj.value("artista").toString();
    c.numeroTracce = obj.value("numero_tracce").toInt();

    return new Cd(b.titolo.toStdString(), b.annoPubblicazione.toStdString(), b.id.toStdString(),
                           b.genere.toStdString(), b.immagine.toStdString(), b.lingua.toStdString(),
                           b.copieTotali, m.supportoTecnologico.toStdString(), m.casaDiProduzione.toStdString(),
                           m.durata, c.artista.toStdString(), c.numeroTracce, b.copieInPrestito, a.ascoltato);
}


//operazione di salvataggio di un oggetto Biblioteca nella lista e scrittura nel file Json
void JsonManager::saveNewObject(Biblioteca* b) {
    bibliotecaList.append(b);
    QJsonArray arr;

    if(!readJsonArray(arr)) {
        qWarning() << "Creazione nuovo array vuoto";
        arr = QJsonArray();
    }

    QJsonObject obj;
    // chiamata al giusto save che restituirà l'oggetto json da aggiungere al QJsonArray arr
    // TODO aggiungere nuove classi
    if (auto p = dynamic_cast<Media_video*>(b)) {
        obj = save(p);
    } else if (auto p = dynamic_cast<Libro*>(b)) {
        obj = save(p);
    } else if (auto p = dynamic_cast<Periodico*>(b)) {
        obj = save(p);
    } else if (auto p = dynamic_cast<Cd*>(b)) {
        obj = save(p);
    }
    else {
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

void JsonManager::save(const Multimedia* m, QJsonObject& obj) const {
    obj["supportoTecnologico"] = QString::fromStdString(m->getSupportoTecnologico());
    obj["casaDiProduzione"] = QString::fromStdString(m->getCasaDiProduzione());
    obj["durata"] = QString::number(m->getDurata());
}

void JsonManager::save(const Media_cartaceo* c, QJsonObject& obj) const {
    obj["numeroPagine"] = c->getNumeroPagine();
    obj["editore"] = QString::fromStdString(c->getEditore());
    obj["letto"] = c->getLetto();
}

void JsonManager::save(const Media_audio* m, QJsonObject& obj) const {
    obj["ascoltato"] = m->getAscoltato();
}

// ritorna l'oggetto Json da salvare completo
QJsonObject JsonManager::save(const Media_video* video) const {
    QJsonObject obj;
    obj["Classe"] = "Media_video";
    save(static_cast<const Biblioteca*>(video), obj);
    save(static_cast<const Multimedia*>(video), obj);

    obj["regista"] = QString::fromStdString(video->getRegista());
    obj["guardato"] = video->getGuardato();

    return obj;
}

QJsonObject JsonManager::save(const Periodico* periodico) const {
    QJsonObject obj;
    obj["Classe"] = "Periodico";
    save(static_cast<const Biblioteca*>(periodico), obj);
    save(static_cast<const Media_cartaceo*>(periodico), obj);

    obj["periodo"] = QString::fromStdString(periodico->periodoToString());
    obj["diffusione"] = QString::fromStdString(periodico->diffusioneToString());
    obj["numeroArticoli"] = periodico->getNumeroArticoli();
    obj["data"] = QString::fromStdString(periodico->getData());

    return obj;
}

QJsonObject JsonManager::save(const Libro* libro) const {
    QJsonObject obj;
    obj["Classe"] = "Libro";
    save(static_cast<const Biblioteca*>(libro), obj);
    save(static_cast<const Media_cartaceo*>(libro), obj);

    obj["autore"] = QString::fromStdString(libro->getAutore());
    return obj;
}

QJsonObject JsonManager::save(const Cd* cd) const {
    QJsonObject obj;
    obj["Classe"] = "Cd";
    save(static_cast<const Biblioteca*>(cd), obj);
    save(static_cast<const Multimedia*>(cd), obj);
    save(static_cast<const Media_audio*>(cd), obj);

    obj["artista"] = QString::fromStdString(cd->getArtista());
    obj["numeroTracce"] = cd->getNumeroTracce();

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
    if (auto p = dynamic_cast<Media_video*>(biblio)) {
        obj = save(p);
    } else if (auto p = dynamic_cast<Libro*>(biblio)) {
        obj = save(p);
    } else if (auto p = dynamic_cast<Periodico*>(biblio)) {
        obj = save(p);
    } else if (auto p = dynamic_cast<Cd*>(biblio)) {
        obj = save(p);
    } else {
        qWarning() << "Tipo non supportato in updateObject";
        return;
    }

    //viene sovrascritto il vecchio elemento con quello aggiornato, riscritto l'array e notificati gli observers dell'operazione
    arr[index] = obj;
    writeJsonArray(arr);
    notifyObservers();
}

void JsonManager::savePrenota(Biblioteca* biblio) {
    if (!biblio) return;

    // Prima modifica l'oggetto
    try {
        biblio->preleva();
    } catch (const std::runtime_error& e) {
        qWarning() << "Errore:" << e.what();
        return;
    }

    // Trova l'indice
    int index = -1;
    for (int i = 0; i < bibliotecaList.size(); ++i) {
        if (bibliotecaList[i] == biblio) {
            index = i;
            break;
        }
    }

    if (index == -1) return;

    QJsonArray arr;
    if (!readJsonArray(arr)) return;

    if (index < arr.size()) {
        QJsonObject obj = arr[index].toObject();
        obj["disponibile"] = biblio->getDisponibilita();
        obj["copieInPrestito"] = biblio->getCopieInPrestito();
        arr[index] = obj;

        writeJsonArray(arr);
        notifyObservers();
    }
}

void JsonManager::saveRestituisci(Biblioteca* biblio) {
    if (!biblio) return;

    // Prima modifica l'oggetto in memoria
    try {
        biblio->restituisci();
    } catch (const std::runtime_error& e) {
        qWarning() << "Errore restituisci:" << e.what();
        return;
    }

    if (auto video = dynamic_cast<Media_video*>(biblio)) {
        video->setGuardato(true);  // Quando restituisci un video, lo hai guardato
    } else if (auto cartaceo = dynamic_cast<Media_cartaceo*>(biblio)) {
        cartaceo->setLetto(true);
    } else if (auto audio = dynamic_cast<Media_audio*>(biblio)) {
        audio->setAscoltato(true);
    }

    // Trova l'indice nella lista
    int index = -1;
    for (int i = 0; i < bibliotecaList.size(); ++i) {
        if (bibliotecaList[i] == biblio) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        qWarning() << "Media non trovato nella lista";
        return;
    }

    // Leggi e aggiorna il JSON
    QJsonArray arr;
    if (!readJsonArray(arr)) return;

    if (index < arr.size()) {
        QJsonObject obj = arr[index].toObject();
        obj["disponibile"] = biblio->getDisponibilita();
        obj["copieInPrestito"] = biblio->getCopieInPrestito();
        arr[index] = obj;

        if (auto video = dynamic_cast<Media_video*>(biblio)) {
            obj["guardato"] = video->getGuardato();
        } else if (auto cartaceo = dynamic_cast<Media_cartaceo*>(biblio)) {
            obj["letto"] = cartaceo->getLetto();
        } else if (auto audio = dynamic_cast<Media_audio*>(biblio)) {
            obj["ascoltato"] = audio->getAscoltato();
        }

        if (writeJsonArray(arr)) {
            notifyObservers();
        }
    }
}

void JsonManager::saveGuardato(Media_video* video) {
    int occToSkip = 0;
    for (auto* it : bibliotecaList) {
        if (it == video) break;
        if (it->getTitolo() == video->getTitolo()) ++occToSkip;
    }


    QJsonArray arr; if (!readJsonArray(arr)) return;
    QJsonArray updated; int occ = 0; bool done = false;
    for (const auto& v : arr) {
        auto o = v.toObject();
        if (!done && o.value("titolo").toString() == QString::fromStdString(video->getTitolo())) {
            if (occ == occToSkip) { o["guardato"] = video->getGuardato(); done = true; }
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

void JsonManager::saveAscoltato(Media_audio* audio) {
    int occToSkip = 0;
    for (auto* it : bibliotecaList) {
        if (it == audio) break;
        if (it->getTitolo() == audio->getTitolo()) ++occToSkip;
    }

    QJsonArray arr; if (!readJsonArray(arr)) return;
    QJsonArray updated; int occ = 0; bool done = false;
    for (const auto& v : arr) {
        auto o = v.toObject();
        if (!done && o.value("titolo").toString() == QString::fromStdString(audio->getTitolo())) {
            if (occ == occToSkip) { o["guardato"] = audio->getAscoltato(); done = true; }
            ++occ;
        }
        updated.append(o);
    }
    if (done) writeJsonArray(updated);
    notifyObservers();
}




