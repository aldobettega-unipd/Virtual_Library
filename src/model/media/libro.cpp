#include "libro.h"

Libro::Libro(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
    int numeroPagine, string editore, string autore, int copieInPrestito, bool letto): 
    Media_cartaceo(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, numeroPagine, editore, copieInPrestito,
        letto), autore(autore) {}

Libro::~Libro() {}

string Libro::getAutore() const {
    return autore;
}

void Libro::setAutore(const string& a) {
    autore = a;
}

void Libro::accept(Visitor* visitor) {
    visitor->visit(this);
}
