#include "media_video.h"

Media_video::Media_video(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
        string supportoTecnologico, string casaDiProduzione, int durata, string regista, bool guardato, 
        int copieInPrestito): 
        Multimedia(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, supportoTecnologico, casaDiProduzione,
            durata, copieInPrestito), regista(regista), guardato(guardato) {}

Media_video::~Media_video() {}

string Media_video::getRegista() const {
    return regista;
}

bool Media_video::getGuardato() const {
    return guardato;
}

void Media_video::setRegista(const string& r) {
    regista = r;
}

void Media_video::setGuardato(const bool& b) {
    guardato = b;
}
