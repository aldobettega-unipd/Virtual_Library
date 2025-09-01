#include "fumetto.h"

Fumetto::Fumetto(string titolo, string annoPubblicazione, string id, string genere, string immagine, int copieTotali, int numeroPagine,
        string lingua, string editore, string autore, int numeroVolume, string nomeSaga, string disegnatore, 
        bool colorato, int copieInPrestito, bool letto):
        Libro(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, numeroPagine, editore, autore, copieInPrestito,
            letto), numeroVolume(numeroVolume), nomeSaga(nomeSaga), disegnatore(disegnatore) {}

Fumetto::~Fumetto() {}

int Fumetto::getNumeroVolume() const {
    return numeroVolume;
}

string Fumetto::getNomeSaga() const {
    return nomeSaga;
}

string Fumetto::getDisegnatore() const {
    return disegnatore;
}

bool Fumetto::getColorato() const {
    return colorato;
}

void Fumetto::setNumeroVolume(const int& n) {
    numeroVolume = n;
}

void Fumetto::setNomeSaga(const string& n) {
    nomeSaga = n;
}

void Fumetto::setDisegnatore(const string& d) {
    disegnatore = d;
}

void Fumetto::setColorato(const bool& c) {
    colorato = c;
}
