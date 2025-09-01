#include "media_fisico.h"
#include <stdexcept>

Media_fisico::Media_fisico(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua,
    int copieTotali, int copieInPrestito): Biblioteca(titolo, annoPubblicazione, id, genere, immagine), lingua(lingua),
    copieTotali(copieTotali), copieInPrestito(copieInPrestito) {
        if (copieInPrestito >= copieTotali)
            setDisponibilità(false);
        else
            setDisponibilità(true);
    }

Media_fisico::~Media_fisico() {}

string Media_fisico::getLingua() const {
    return lingua;
}

int Media_fisico::getCopieTotali() const {
    return copieTotali;
}

int Media_fisico::getCopieInPrestito() const {
    return copieInPrestito;
}

bool Media_fisico::getDisponibilità() const {
    return disponibile;
}

void Media_fisico::setLingua(const string& l) {
    lingua = l;
}

void Media_fisico::setCopieTotali(const int& c) {
    copieTotali = c;
}

void Media_fisico::setCopieInPrestito(const int& c) {
    copieInPrestito = c;
}

void Media_fisico::setDisponibilità(const bool& d) {
    disponibile = d;
}

void Media_fisico::restituisci() {
    copieInPrestito -= 1;
    if (disponibile == false)
        setDisponibilità(true);
}

void Media_fisico::preleva() {
    if (copieInPrestito >= copieTotali)
        throw runtime_error("Nessuna copia disponibile");
    copieInPrestito += 1;
    if (copieInPrestito == copieTotali)
        setDisponibilità(false);
}
