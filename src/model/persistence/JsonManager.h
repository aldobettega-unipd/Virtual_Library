#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QList>
#include <QString>

#include "../media/media_video.h"
#include "../media/cd.h"
#include "../media/periodico.h"
#include "../media/libro.h"

class Biblioteca;
class Multimedia;
class Media_cartaceo;
class Media_audio;

class JsonObserver;

//Questa classe consente di operare tra oggetti Json e tutti gli oggetti di tipo Biblioteca in modo granulare,
//quindi con operazioni di salvataggio di una classe o caricamento di un file Json.

class JsonManager : public QObject
{
    Q_OBJECT
public:
    explicit JsonManager(const QString& filePath, QObject* parent = nullptr);
    QList<Biblioteca*> loadBibliotecaListFromJson();
    void addObserver(JsonObserver* obs);

    QString getFilePath() const;

private:
    QList<JsonObserver*> observers;
    QList<Biblioteca*> bibliotecaList;
    QString filePath;

    struct BibliotecaData {
        QString titolo;
        QString id;
        QString annoPubblicazione;
        QString genere;
        QString immagine;
        QString lingua;
        int copieTotali;
        int copieInPrestito;
        bool disponibile;
    };
    struct MultimediaData {
        QString supportoTecnologico;
        QString casaDiProduzione;
        int durata;
    };
    struct MediaCartaceoData {
        int numeroPagine;
        QString editore;
        bool letto;
    };
    struct MediaVideoData {
        QString regista;
        bool guardato;
    };
    struct MediaAudioData {
        bool ascoltato;
    };
    struct PeriodicoData {
        Periodico::Periodo periodo;
        Periodico::Diffusione diffusione;
        int numero_articoli;
        QString data;
    };
    struct LibroData {
        QString autore;
    };
    struct CdData {
        QString artista;
        int numeroTracce;
    };
    struct AudiolibroData {
        QString narratore;
        QString libroOriginale;
    };

    //caricamento
    BibliotecaData loadBiblioteca(const QJsonObject& obj) const;
    MultimediaData loadMultimedia(const QJsonObject& obj) const;
    MediaCartaceoData loadMediaCartaceo(const QJsonObject& obj) const;
    Biblioteca* loadMediaVideo(const QJsonObject& obj) const;
    MediaAudioData loadMediaAudio(const QJsonObject& obj) const;
    Biblioteca* loadPeriodici(const QJsonObject& obj) const;
    Biblioteca* loadLibri(const QJsonObject& obj) const;
    Biblioteca* loadCd(const QJsonObject& obj) const;

    //salvataggio
    void save(const Biblioteca* b, QJsonObject& obj) const;
    void save(const Multimedia* m, QJsonObject& obj) const;
    void save(const Media_cartaceo* c, QJsonObject& obj) const;
    void save(const Media_audio* a, QJsonObject& obj) const;

    QJsonObject save(const Media_video* video) const;
    QJsonObject save(const Periodico* periodico) const;
    QJsonObject save(const Libro* libro) const;
    QJsonObject save(const Cd* cd) const;

    //utilità
    void notifyObservers();
    bool readJsonArray(QJsonArray& out) const;
    bool writeJsonArray(QJsonArray& in) const;

public slots:
    void saveNewObject(Biblioteca* obj);
    void updateObject(Biblioteca* obj);
    void deleteObject(Biblioteca* obj);

    void savePrenota(Biblioteca* biblio);
    void saveRestituisci(Biblioteca* biblio);

    void saveGuardato(Media_video* video);
    void saveLetto(Media_cartaceo* cartaceo);
    void saveAscoltato(Media_audio* audio);
};

#endif // JSONMANAGER_H
