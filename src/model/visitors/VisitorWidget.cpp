#include "VisitorWidget.h"
/*
#include "../media/media_video.h"
#include "../media/serie_tv.h"
#include "../media/cd.h"
#include "../media/audiolibro.h"
#include "../media/periodico.h"
*/
#include "../media/libro.h"
//#include "../media/fumetto.h"

#include <QPushButton>

VisitorWidget::VisitorWidget(QWidget* parent) :
    QWidget(parent), widget(new QWidget(this)), mainLayout(new QHBoxLayout(widget)), leftContainerLayout(new QVBoxLayout),
    image(new QLabel), pulsantieraLayout(new QHBoxLayout), descrizioneLayout(new QVBoxLayout)
{

    leftContainerLayout->addWidget(image);
    leftContainerLayout->addLayout(pulsantieraLayout);

    mainLayout->addLayout(leftContainerLayout);
    mainLayout->addLayout(descrizioneLayout);
}

QWidget* VisitorWidget::getWidget() const{
    return widget;
}

// Implementazione dei visit

void VisitorWidget::visit(Biblioteca *biblio) {
    if (!biblio) return;
    // Pulizia SOLO della descrizione e della pulsantiera
    QLayoutItem* child;
    while ((child = descrizioneLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
    while ((child = pulsantieraLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
    // Setup immagine
    QString imagePath = QString::fromStdString(biblio->getImmagine());
    QPixmap pixmap(imagePath);
    image->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
    image->setAlignment(Qt::AlignCenter);
    image->setFixedSize(120, 160);
    image->setStyleSheet("border: 1px solid #ccc; background: #f0f0f0;");

    //aggiunta di tasti alla pulsantiera
    QPushButton* prenota = new QPushButton("Prenota", this);
    QPushButton* restituisci = new QPushButton("Restituisci", this);
    pulsantieraLayout->addWidget(prenota);
    pulsantieraLayout->addWidget(restituisci);

    // Descrizione
    QLabel* titolo = new QLabel(QString("Titolo: %1").arg(QString::fromStdString(biblio->getTitolo())), this);
    QLabel* annoPubblicazione = new QLabel(
        QString("Anno di Pubblicazione: %1").arg(QString::fromStdString(biblio->getAnnoPubblicazione())), this);
    QLabel* id = new QLabel(QString("Id: %1").arg(QString::fromStdString(biblio->getId())), this);
    QLabel* genere = new QLabel(QString("Genere: %1").arg(QString::fromStdString(biblio->getGenere())), this);
    QLabel* lingua = new QLabel(QString("Lingua: %1").arg(QString::fromStdString(biblio->getLingua())), this);
    QLabel* copieTotali = new QLabel(QString("Copie totali: %1").arg((biblio->getCopieTotali())), this);
    //Labmda che dinamicamente indica la disponibilità dell'articolo
    QLabel* disponibile = new QLabel([biblio]() {  // ← [media_fisico] non [&media_fisico]
        if (biblio && biblio->getDisponibilità())
            return QString("✅ L'articolo è disponibile");
        else
            return QString("❌ L'articolo non è disponibile");
    }(), this);

    descrizioneLayout->addWidget(titolo);
    descrizioneLayout->addWidget(annoPubblicazione);
    descrizioneLayout->addWidget(id);
    descrizioneLayout->addWidget(genere);
    descrizioneLayout->addWidget(lingua);
    descrizioneLayout->addWidget(copieTotali);
    descrizioneLayout->addWidget(disponibile);

}

/*
void VisitorWidget::visit(Multimedia* multimedia) {

}*/

void VisitorWidget::visit(Media_cartaceo* media_cartaceo) {
    //chiamata del visit padre
    visit(static_cast<Biblioteca*>(media_cartaceo));

    // Aggiunta a Descrizione
    QLabel* numero_pagine = new QLabel(QString("Numero di pagine: %1").arg((media_cartaceo->getNumeroPagine())), this);
    QLabel* editore = new QLabel(QString("Editore: %1").arg(QString::fromStdString(media_cartaceo->getEditore())), this);
    QLabel* letto = new QLabel([media_cartaceo]() {  // ← Cattura per valore
        if (media_cartaceo && media_cartaceo->getLetto())
            return QString("📖 L'articolo è già stato letto");
        else
            return QString("🔖 L'articolo è ancora da leggere");
    }(), this);

    descrizioneLayout->addWidget(numero_pagine);
    descrizioneLayout->addWidget(editore);
    descrizioneLayout->addWidget(letto);
}
/*
void VisitorWidget::visit(Media_video* media_video) {
    // codice per gestire Media_video
}

void VisitorWidget::visit(Serie_tv* serie_tv) {
    // codice per gestire Serie_tv
}

void VisitorWidget::visit(Cd* cd) {
    // codice per gestire Cd
}

void VisitorWidget::visit(Audiolibro* audiolibro) {
    // codice per gestire Audiolibro
}

void VisitorWidget::visit(Periodico* periodico) {
    // codice per gestire Periodico
}*/

void VisitorWidget::visit(Libro* libro) {
    //chiamata del visit padre
    visit(static_cast<Media_cartaceo*>(libro));

    // codice per gestire Libro
    QLabel* autore = new QLabel(QString("Autore: %1").arg(QString::fromStdString(libro->getAutore())), this);

    descrizioneLayout->addWidget(autore);
}
/*
void VisitorWidget::visit(Fumetto* fumetto) {
    // codice per gestire Fumetto
}*/


