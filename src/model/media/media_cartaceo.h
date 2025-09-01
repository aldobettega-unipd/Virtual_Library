#pragma once
#include "biblioteca.h"
#include <string>

class Media_cartaceo: public Biblioteca {
private:
    int numeroPagine;
    string editore;
    bool letto;
public:
    Media_cartaceo(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        int numeroPagine, string editore, int copieInPrestito=0, bool letto=false);
    virtual ~Media_cartaceo();
    virtual int getNumeroPagine() const;
    virtual string getEditore() const;
    virtual bool getLetto() const;
    virtual void setNumeroPagine(const int&);
    virtual void setEditore(const string&);
    virtual void accept(Visitor* visitor) override = 0;
};
