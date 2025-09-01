#include "multimedia.h"

Multimedia::Multimedia(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua,
    int copieTotali, string supportoTecnologico, string casaDiProduzione, int durata, int copieInPrestito):
        Biblioteca(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, copieInPrestito),
        supportoTecnologico(supportoTecnologico), casaDiProduzione(casaDiProduzione), durata(durata) {}

Multimedia::~Multimedia() {}

string Multimedia::getSupportoTecnologico() const {
    return supportoTecnologico;
}

string Multimedia::getCasaDiProduzione() const {
    return casaDiProduzione;
}

int Multimedia::getDurata() const {
    return durata;
}

void Multimedia::setSupportoTecnologico(const string& s) {
    supportoTecnologico = s;
}

void Multimedia::setCasaDiProduzione(const string& c) {
    casaDiProduzione = c;
}

void Multimedia::setDurata(const int& d) {
    durata = d;
} 
