#include "periodico.h"
#include <stdexcept>

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

Periodico::Periodo Periodico::stringToPeriodo(const std::string& str) {
    if (str == "Giornaliero") return Giornaliero;
    if (str == "Settimanale") return Settimanale;
    if (str == "Mensile") return Mensile;
    throw std::invalid_argument("Periodo non valido: " + str);
}

Periodico::Diffusione Periodico::stringToDiffusione(const std::string& str) {
    if (str == "Provinciale") return Provinciale;
    if (str == "Regionale") return Regionale;
    if (str == "Nazionale") return Nazionale;
    if (str == "Internazionale") return Internazionale;
    throw std::invalid_argument("Diffusione non valida: " + str);
}

void Periodico::accept(Visitor* visitor) {
    visitor->visit(this);
}
