#pragma once
#include "media_cartaceo.h"
#include <string>

class Periodico: public Media_cartaceo {
public:
    enum Periodo{Giornaliero, Settimanale, Mensile};
    enum Diffusione{Provinciale,Regionale,Nazionale,Internazionale};
private:
    Periodo periodo;
    Diffusione diffusione;
    int numeroArticoli;
    string data;
public:
    Periodico(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        int numeroPagine, string editore, Periodo periodo, Diffusione diffusione, int numeroArticoli, string data, 
        int copieInPrestito=0, bool letto=false);
    virtual ~Periodico();
    Periodo getPeriodo() const;
    Diffusione getDiffusione() const;
    int getNumeroArticoli() const;
    string getData() const;

    string periodoToString() const;
    string diffusioneToString() const;

    void setPeriodo(const Periodo&);
    void setDiffusione(const Diffusione&);
    void setNumeroArticoli(const int&);
    void setData(const string&);

    static Periodo stringToPeriodo(const std::string& str);
    static Diffusione stringToDiffusione(const std::string& str);

    virtual void accept(Visitor* visitor) override;
};
