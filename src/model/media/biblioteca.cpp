#include "biblioteca.h"
#include <stdexcept>

using namespace std;

Biblioteca::Biblioteca(string titolo, string annoPubblicazione, string id, string genere, string immagine, string lingua, int copieTotali,
                       int copieInPrestito):
    titolo(titolo), annoPubblicazione(annoPubblicazione), id(id), genere(genere), immagine(immagine), lingua(lingua), copieTotali(copieTotali),
    copieInPrestito(copieInPrestito), disponibile(copieInPrestito < copieTotali)
{}

Biblioteca::~Biblioteca() {}

string Biblioteca::getTitolo() const {
    return titolo;
}

string Biblioteca::getAnnoPubblicazione() const {
    return annoPubblicazione;
}

string Biblioteca::getId() const {
    return id;
}

string Biblioteca::getGenere() const {
    return genere;
}

string Biblioteca::getImmagine() const {
    return immagine;
}

string Biblioteca::getLingua() const {
    return lingua;
}

int Biblioteca::getCopieTotali() const {
    return copieTotali;
}

int Biblioteca::getCopieInPrestito() const {
    return copieInPrestito;
}

bool Biblioteca::getDisponibilita() const {
    return disponibile;
}

void Biblioteca::setTitolo(const string& t) {
    titolo = t;
}

void Biblioteca::setAnnoPubblicazione(const string& a) {
    annoPubblicazione = a;
}

void Biblioteca::setId(const string& i) {
    id = i;
}

void Biblioteca::setGenere(const string& g) {
    genere = g;
}

void Biblioteca::setImmagine(const string& i) {
    immagine = i;
}

void Biblioteca::setLingua(const string& l) {
    lingua = l;
}

void Biblioteca::setCopieTotali(const int& c) {
    copieTotali = c;
}

void Biblioteca::setCopieInPrestito(const int& c) {
    copieInPrestito = c;
}

void Biblioteca::setDisponibilita(const bool& d) {
    disponibile = d;
}

void Biblioteca::restituisci() {
    if (copieInPrestito <= 0)
        throw runtime_error("Nessuna copia da restituire");
    copieInPrestito--;
    disponibile = true;
}

void Biblioteca::preleva() {
    if (copieInPrestito >= copieTotali)
        throw runtime_error("Nessuna copia disponibile");
    copieInPrestito += 1;
    if (copieInPrestito == copieTotali)
        setDisponibilita(false);
}


