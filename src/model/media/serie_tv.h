#pragma once
#include "media_video.h"
#include <string>

class Serie_tv: public Media_video {
private:
    int numeroTotaleEpisodi;
    int numeroStagioni;
    int numeroDvd;
public:
    Serie_tv(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string regista, int numeroTotaleEpisodi,
        int numeroStagioni = 1, int numeroDvd = 1, bool guardato = false, int copieInPrestito=0);
    virtual ~Serie_tv();
    virtual int getNumeroTotaleEpisodi() const;
    virtual int getNumeroStagioni() const;
    virtual int getNumeroDvd() const;
    virtual void setNumeroTotaleEpisodi(const int&);
    virtual void setNumeroStagioni(const int&);
    virtual void setNumeroDvd(const int&);
};
