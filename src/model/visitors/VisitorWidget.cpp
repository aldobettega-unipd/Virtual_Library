#include "VisitorWidget.h"
/*
#include "../media/audiolibro.h"
*/
#include "../media/media_video.h"
#include "../media/cd.h"
#include "../media/periodico.h"
#include "../media/libro.h"

#include <QPushButton>

VisitorWidget::VisitorWidget(QWidget* parent) :
    QWidget(parent), widget(new QWidget(this)), mainLayout(new QHBoxLayout(widget)), image(new QLabel),
    descrizioneContainer(new QWidget(widget)), descrizioneLayout(new QFormLayout(descrizioneContainer))
{
    mainLayout->addWidget(image);
    mainLayout->addLayout(descrizioneLayout);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(image, 1);
    mainLayout->addWidget(descrizioneContainer, 1);
    descrizioneContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    image->setAlignment(Qt::AlignCenter);
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    image->setMinimumSize(200, 300);
    image->setStyleSheet("QLabel { border: 1px solid #ccc; background: #f0f0f0; }");

    descrizioneLayout->setSpacing(10);
    descrizioneLayout->setContentsMargins(10, 10, 10, 10);
    descrizioneContainer->setStyleSheet("QLabel { font-size: 14pt; }");
}

QWidget* VisitorWidget::getWidget() const{
    return widget;
}


// Implementazione dei visit

void VisitorWidget::visit(Biblioteca *biblio) {
    if (!biblio) return;
    // Pulizia della descrizione e della pulsantiera
    QLayoutItem* child;
    while ((child = descrizioneLayout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
    // Setup immagine
    QString imagePath = QString::fromStdString(biblio->getImmagine());
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        image->setPixmap(pixmap.scaled(image->width(), image->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        image->setText("🖼️\nImmagine non disponibile");
        image->setAlignment(Qt::AlignCenter);
    }

    // Descrizione
    descrizioneLayout->addRow("Titolo:", new QLabel(QString::fromStdString(biblio->getTitolo())));
    descrizioneLayout->addRow("Anno Pubblicazione:", new QLabel(QString::fromStdString(biblio->getAnnoPubblicazione())));
    descrizioneLayout->addRow("Genere:", new QLabel(QString::fromStdString(biblio->getGenere())));
    descrizioneLayout->addRow("Lingua:", new QLabel(QString::fromStdString(biblio->getLingua())));
    descrizioneLayout->addRow("Id: ", new QLabel(QString::fromStdString(biblio->getId())));

    QLabel* statusLabel = new QLabel();
    int copieDisponibili = biblio->getCopieTotali() - biblio->getCopieInPrestito();
    if (copieDisponibili > 0) {
        // Se ci sono copie, mostra quante e usa il colore verde
        statusLabel->setText(QString("Disponibile (%1)").arg(copieDisponibili));
        statusLabel->setStyleSheet("color: green; font-weight: bold;");
    } else {
        // Altrimenti, mostra non disponibile in rosso
        statusLabel->setText("Non disponibile");
        statusLabel->setStyleSheet("color: red; font-weight: bold;");
    }

    descrizioneLayout->addRow("Disponibilità:", statusLabel);
}


void VisitorWidget::visit(Multimedia* multimedia) {
    //chiamata del visit padre
    visit(static_cast<Biblioteca*>(multimedia));

    descrizioneLayout->addRow("Supporto tecnologico: ", new QLabel(QString::fromStdString(multimedia->getSupportoTecnologico())));
    descrizioneLayout->addRow("Casa di produzione: ", new QLabel(QString::fromStdString(multimedia->getCasaDiProduzione())));
    descrizioneLayout->addRow("Durata: ", new QLabel(QString::number(multimedia->getDurata())));
}

void VisitorWidget::visit(Media_cartaceo* media_cartaceo) {
    //chiamata del visit padre
    visit(static_cast<Biblioteca*>(media_cartaceo));

    // Aggiunta a Descrizione
    descrizioneLayout->addRow("Numero di pagine: ", new QLabel(QString::number(media_cartaceo->getNumeroPagine())));
    descrizioneLayout->addRow("Editore: ", new QLabel(QString::fromStdString(media_cartaceo->getEditore())));

    QString lettoText = media_cartaceo->getLetto() ? "Già letto" : "Ancora da leggere";
    QLabel* lettoLabel = new QLabel(lettoText);
    descrizioneLayout->addRow("Letto:", lettoLabel);
}

void VisitorWidget::visit(Media_video* media_video) {
    // chiamata del visit padre
    visit(static_cast<Multimedia*>(media_video));

    descrizioneLayout->addRow("Regista: ", new QLabel(QString::fromStdString(media_video->getRegista())));

    QString guardatoText = media_video->getGuardato() ? "Già guardato" : "Ancora da gurdare";
    QLabel* guardatoLabel = new QLabel(guardatoText);
    descrizioneLayout->addRow("Guardato:", guardatoLabel);
}

void VisitorWidget::visit(Media_audio* media_audio) {
    // chiamata del visito padre
    visit(static_cast<Multimedia*>(media_audio));

    QString ascoltatoText = media_audio->getAscoltato() ? "Già ascoltato" : "Ancora da gurdare";
    QLabel* ascoltatoLabel = new QLabel(ascoltatoText);
    descrizioneLayout->addRow("Guardato:", ascoltatoLabel);
}

/*

void VisitorWidget::visit(Audiolibro* audiolibro) {
    // codice per gestire Audiolibro
}
*/

void VisitorWidget::visit(Periodico* periodico) {
    //chiamata del visit padre
    visit(static_cast<Media_cartaceo*>(periodico));

    descrizioneLayout->addRow("Periodo:", new QLabel(QString::fromStdString(periodico->periodoToString())));
    descrizioneLayout->addRow("Diffusione: ", new QLabel(QString::fromStdString(periodico->diffusioneToString())));
    descrizioneLayout->addRow("Numero articoli: ", new QLabel(QString::number((periodico->getNumeroArticoli()))));
    descrizioneLayout->addRow("Data: ", new QLabel(QString::fromStdString(periodico->getData())));
}

void VisitorWidget::visit(Libro* libro) {
    //chiamata del visit padre
    visit(static_cast<Media_cartaceo*>(libro));

    descrizioneLayout->addRow("Autore: ", new QLabel(QString::fromStdString(libro->getAutore())));
}

void VisitorWidget::visit(Cd* cd) {
    // chiamata del visit padre
    visit(static_cast<Media_audio*>(cd));

    descrizioneLayout->addRow("Artista:", new QLabel(QString::fromStdString(cd->getArtista())));
    descrizioneLayout->addRow("Numero tracce:", new QLabel(QString::number(cd->getNumeroTracce())));
}


