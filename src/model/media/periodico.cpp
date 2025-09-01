#include "periodico.h"

Periodico::Periodico(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
    int numeroPagine, string editore, Periodo periodo, Diffusione diffusione, int numeroArticoli, string data, 
        int copieInPrestito, bool letto):
        Media_cartaceo(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, numeroPagine, editore, copieInPrestito,
             letto), periodo(periodo), diffusione(diffusione), numeroArticoli(numeroArticoli), data(data) {}

Periodico::~Periodico() {}

string Periodico::periodoToString() const {
    switch (periodo) {
    case Giornaliero: return "Giornaliero";
    case Settimanale: return "Settimanale";
    case Mensile: return "Mensile";
    default: return "Sconosciuto";
    }
}

string Periodico::diffusioneToString() const {
    switch (diffusione) {
        case Provinciale: return "Provinciale";
        case Regionale: return "Regionale";
        case Nazionale: return "Nazionale";
        case Internazionale: return "Internazionale";
        default: return "Sconosciuto";
    }
}

int Periodico::getNumeroArticoli() const {
    return numeroArticoli;
}

string Periodico::getData() const {
    return data;
}

void Periodico::setPeriodo(const Periodico::Periodo& p) {
    periodo = p;
}

void Periodico::setDiffusione(const Periodico::Diffusione& d) {
    diffusione = d;
}

void Periodico::setNumeroArticoli(const int& n) {
    numeroArticoli = n;
}

void Periodico::setData(const string& d) {
    data = d;
}
