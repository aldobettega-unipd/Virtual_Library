#pragma once
#include "biblioteca.h"
#include <string>

class Multimedia: public Biblioteca {
private:
    string supportoTecnologico;
    string casaDiProduzione;
    int durata;
public:
    Multimedia(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, int copieInPrestito=0);
    virtual ~Multimedia();
    virtual string getSupportoTecnologico() const;
    virtual string getCasaDiProduzione() const;
    virtual int getDurata() const;
    virtual void setSupportoTecnologico(const string&);
    virtual void setCasaDiProduzione(const string&);
    virtual void setDurata(const int&);
    virtual void accept(Visitor* visitor) override = 0;
};
