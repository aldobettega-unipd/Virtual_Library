#pragma once
#include "multimedia.h"
#include <string>

class Media_video: public Multimedia {
private:
    string regista;
    bool guardato;
public:
    Media_video(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string regista, bool guardato = false,
        int copieInPrestito=0);
    virtual ~Media_video();
    virtual string getRegista() const;
    virtual bool getGuardato() const;
    virtual void setRegista(const string&);
    virtual void setGuardato(const bool&);
    virtual void accept(Visitor* visitor) override = 0;
};
