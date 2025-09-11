#include "media_cartaceo.h"

Media_cartaceo::Media_cartaceo(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
    int numeroPagine, string editore, int copieInPrestito,  bool letto):
    Biblioteca(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, copieInPrestito), numeroPagine(numeroPagine),
    editore(editore), letto(letto) {}

Media_cartaceo::~Media_cartaceo() {}

int Media_cartaceo::getNumeroPagine() const {
    return numeroPagine;
}

string Media_cartaceo::getEditore() const {
    return editore;
}

bool Media_cartaceo::getLetto() const {
    return letto;
}

void Media_cartaceo::setNumeroPagine(const int& n) {
    numeroPagine = n;
}

void Media_cartaceo::setEditore(const string& e) {
    editore = e;
}

void Media_cartaceo::setLetto(const bool& l) {
    letto = l;
}
