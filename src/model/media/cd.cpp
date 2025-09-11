#include "cd.h"

Cd::Cd(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string artista, int numero_tracce,
        bool ascoltato, int copieInPrestito):
        Media_audio(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, supportoTecnologico, casaDiProduzione,
            durata, ascoltato, copieInPrestito),
    artista(artista), numero_tracce(numero_tracce)
{}

Cd::~Cd() {}

string Cd::getArtista() const {
    return artista;
}

int Cd::getNumeroTracce() const {
    return numero_tracce;
}

void Cd::setArtista(const string& a) {
    artista = a;
}

void Cd::setNumeroTracce(const int& n) {
    numero_tracce = n;
}

void Cd::accept(Visitor* visitor) {
    visitor->visit(this);
}
