#pragma once
#include "media_audio.h"
#include <string>

class Cd: public Media_audio {
private:
    string artista;
    string album;
    int numero_tracce;
public:
    Cd(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string artista, string album, int numero_tracce,
        bool ascoltato=false, int copieInPrestito=0);
    virtual ~Cd();
    virtual string getArtista() const;
    virtual string getAlbum() const;
    virtual int getNumeroTracce() const;
    virtual void setArtista(const string&);
    virtual void setAlbum(const string&);
    virtual void setNumeroTracce(const int&);
};
