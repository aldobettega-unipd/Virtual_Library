#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QList>
#include <QString>

#include "../media/libro.h"

class Biblioteca;
class Media_cartaceo;
class Media_audio;
class Media_video;

class JsonObserver;

//Questa classe consente di operare tra oggetti Json e tutti gli oggetti di tipo Biblioteca in modo granulare,
//quindi con operazioni di salvataggio di una classe o caricamento di un file Json.


class JsonManager : public QObject
{
    Q_OBJECT
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
        QString supportoTecnico;
        QString casaDiProduzione;
        QString durata;
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
        QString periodo;
        QString diffusione;
        int numero_articoli;
        QString data;
    };
    struct LibroData {
        QString autore;
    };
    struct SerieTvData {
        int numeroEpisodi;
        int numeroStagioni;
        int numeroDvd;
    };
    struct CdData {
        QString artista;
        QString album;
        QString numeroTracce;
    };
    struct AudiolibroData {
        QString narratore;
        QString libroOriginale;
    };
    struct FumettoData {
        QString nomeSaga;
        int numeroVolume;
        QString disegnatore;
        bool colorato;
    };

    //helpers di caricamento
    BibliotecaData loadBiblioteca(const QJsonObject& obj) const;
    MediaCartaceoData loadMediaCartaceo(const QJsonObject& obj) const;
    Biblioteca* loadLibri(const QJsonObject& obj) const;

    //helpers di salvataggio
    void save(const Biblioteca* b, QJsonObject& obj) const;
    void save(const Media_cartaceo* c, QJsonObject& obj) const;

    QJsonObject save(const Libro* libro) const;

    //utilità
    void notifyObservers();
    bool readJsonArray(QJsonArray& out) const;
    bool writeJsonArray(QJsonArray& in) const;


public slots:
    void saveNewObject(Biblioteca* obj);
    void updateObject(Biblioteca* obj);
    void deleteObject(Biblioteca* obj);

    void savePrenota(Biblioteca* biblio);
    void saveLetto(Media_cartaceo* cartaceo);
    //void saveAscoltato(Media_audio* audio);
    //void saveVisto(Media_video* video);
public:
    explicit JsonManager(const QString& filePath, QObject* parent = nullptr);
    QList<Biblioteca*> loadBibliotecaListFromJson();
    void addObserver(JsonObserver* obs);

};

#endif // JSONMANAGER_H
