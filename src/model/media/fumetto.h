#pragma once
#include "libro.h"

class Fumetto: public Libro {
private:
    int numeroVolume;
    string nomeSaga;
    string disegnatore;
    bool colorato;
public:
    Fumetto(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
            int numeroPagine, string editore, string autore, int numeroVolume, string nomeSaga, string disegnatore, bool colorato,
            int copieInPrestito=0, bool letto=false);
    virtual ~Fumetto();
    virtual int getNumeroVolume() const;
    virtual string getNomeSaga() const;
    virtual string getDisegnatore() const;
    virtual bool getColorato() const;
    virtual void setNumeroVolume(const int&);
    virtual void setNomeSaga(const string&);
    virtual void setDisegnatore(const string&);
    virtual void setColorato(const bool&);
};
