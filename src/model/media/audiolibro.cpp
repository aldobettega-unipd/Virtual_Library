#include "audiolibro.h"

Audiolibro::Audiolibro(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string narratore, string libroOriginale, 
        bool ascoltato, int copieInPrestito): 
        Media_audio(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, supportoTecnologico,
            casaDiProduzione, durata, ascoltato, copieInPrestito), narratore(narratore), libroOriginale(libroOriginale) {}

Audiolibro::~Audiolibro() {}

string Audiolibro::getNarratore() const {
    return narratore;
}

string Audiolibro::getLibroOriginale() const {
    return libroOriginale;
}

void Audiolibro::setNarratore(const string& n) {
    narratore = n;
}

void Audiolibro::setLibroOriginale(const string& l) {
    libroOriginale = l;
}
