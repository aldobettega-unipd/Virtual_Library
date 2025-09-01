#include "serie_tv.h"

Serie_tv::Serie_tv(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
                   string supportoTecnologico, string casaDiProduzione, int durata, string regista, 
                   int numeroTotaleEpisodi, int numeroStagioni, int numeroDvd, bool guardato, int copieInPrestito): 
                   Media_video(titolo, annoPubblicazione, id, genere, immagine, lingua, copieTotali, supportoTecnologico,
                    casaDiProduzione, durata, regista, guardato, copieInPrestito),
                   numeroTotaleEpisodi(numeroTotaleEpisodi), numeroStagioni(numeroStagioni), numeroDvd(numeroDvd) {}

Serie_tv::~Serie_tv() {}

int Serie_tv::getNumeroTotaleEpisodi() const {
    return numeroTotaleEpisodi;
}

int Serie_tv::getNumeroStagioni() const {
    return numeroStagioni;
}

int Serie_tv::getNumeroDvd() const {
    return numeroDvd;
}

void Serie_tv::setNumeroTotaleEpisodi(const int& numero) {
    numeroTotaleEpisodi = numero;
}

void Serie_tv::setNumeroStagioni(const int& numero) {
    numeroStagioni = numero;
}

void Serie_tv::setNumeroDvd(const int& numero) {
    numeroDvd = numero;
}
