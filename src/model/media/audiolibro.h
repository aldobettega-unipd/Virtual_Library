#pragma once
#include "media_audio.h"

class Audiolibro: public Media_audio {
private:
    string narratore;
    string libroOriginale;
public:
    Audiolibro(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string narratore, string libroOriginale, 
        bool ascoltato=false, int copieInPrestito=0);
    virtual ~Audiolibro();
    virtual string getNarratore() const;
    virtual string getLibroOriginale() const;
    virtual void setNarratore(const string&);
    virtual void setLibroOriginale(const string&);
};
