#pragma once
#include <string>
#include "../visitors/Visitor.h"

using namespace std;

class Biblioteca
{
private:
    string titolo;
    string annoPubblicazione;
    string id;
    string genere;
    string immagine;
    string lingua;
    int copieTotali;
    int copieInPrestito;
    bool disponibile;
public:
    Biblioteca(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
               int copieInPrestito=0);
    virtual ~Biblioteca();
    virtual string getTitolo() const;
    virtual string getAnnoPubblicazione() const;
    virtual string getId() const;
    virtual string getGenere() const;
    virtual string getImmagine() const;
    virtual string getLingua() const;
    virtual int getCopieTotali() const;
    virtual int getCopieInPrestito() const;
    virtual bool getDisponibilita() const;
    virtual void setTitolo(const string&);
    virtual void setAnnoPubblicazione(const string&);
    virtual void setId(const string&);
    virtual void setGenere(const string&);
    virtual void setImmagine(const string&);
    virtual void setLingua(const string&);
    virtual void setCopieTotali(const int&);
    virtual void setCopieInPrestito(const int&);
    virtual void setDisponibilita(const bool&);
    virtual void restituisci();
    virtual void preleva();
    virtual void accept(Visitor* visitor) = 0;
};
