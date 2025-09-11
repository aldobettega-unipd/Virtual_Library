#pragma once
#include "multimedia.h"
#include <string>

class Media_audio: public Multimedia {
private:
    bool ascoltato;
public:
    Media_audio(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, bool ascoltato=false, int copieInPrestito=0);
    virtual ~Media_audio();
    virtual bool getAscoltato() const;
    virtual void setAscoltato(const bool&);
    virtual void accept(Visitor* visitor) override;
};
