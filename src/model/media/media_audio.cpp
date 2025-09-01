#include "media_audio.h"

Media_audio::Media_audio(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, bool ascoltato, int copieInPrestito):
        Multimedia(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, supportoTecnologico, casaDiProduzione,
            durata, copieInPrestito), ascoltato(ascoltato) {}

Media_audio::~Media_audio() {}

bool Media_audio::getAscoltato() const {
    return ascoltato;
}

void Media_audio::setAscoltato(const bool& a) {
    ascoltato = a;
}
