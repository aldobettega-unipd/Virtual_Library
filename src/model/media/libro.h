#pragma once
#include "media_cartaceo.h"
#include "../visitors/Visitor.h"

class Libro: public Media_cartaceo {
private:
    string autore;
public:
    Libro(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        int numeroPagine, string editore, string autore, int copieInPrestito=0, bool letto=false);
    virtual ~Libro();
    virtual string getAutore() const;
    virtual void setAutore(const string&);
    virtual void accept(Visitor* visitor) override;
};
