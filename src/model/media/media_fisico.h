#pragma once
#include "biblioteca.h"

class Media_fisico: public Biblioteca {
private:
    string lingua;
    int copieTotali;
    int copieInPrestito;
    bool disponibile;
public:
    Media_fisico(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        int copieInPrestito=0);
    virtual ~Media_fisico();
    virtual string getLingua() const;
    virtual int getCopieTotali() const;
    virtual int getCopieInPrestito() const;
    virtual bool getDisponibilità() const;
    virtual void setLingua(const string&);
    virtual void setCopieTotali(const int&);
    virtual void setCopieInPrestito(const int&);
    virtual void setDisponibilità(const bool&);
    virtual void restituisci();
    virtual void preleva();
    virtual void accept(Visitor* visitor) override = 0;
};
