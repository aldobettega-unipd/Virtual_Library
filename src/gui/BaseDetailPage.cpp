#include "BaseDetailPage.h"
#include <QScrollArea>
#include "../model/media/biblioteca.h"

BaseDetailPage::BaseDetailPage(QWidget* parent) : QWidget(parent), currentMedia(nullptr), visitorWidget(nullptr)
{
    setupCommonUI();
    setupCommonConnections();
}

void BaseDetailPage::setupCommonUI() {
    mainLayout = new QVBoxLayout(this);

    // Header con pulsante back
    headerWidget = new QWidget(this);
    headerLayout = new QHBoxLayout(headerWidget);

    backButton = new QPushButton("← Indietro", this);
    titleLabel = new QLabel("Dettaglio Media", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    headerLayout->addWidget(backButton);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();

    // Area contenuto scrollabile
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    contentArea = new QWidget(scrollArea);
    contentLayout = new QVBoxLayout(contentArea);

    scrollArea->setWidget(contentArea);

    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(scrollArea);
}

void BaseDetailPage::setupCommonConnections() {
    connect(backButton, &QPushButton::clicked, this, &BaseDetailPage::onBackClicked);
}

void BaseDetailPage::setMediaData(Biblioteca* media) {
    if (!media) return;
    currentMedia = media;
    clearContent();

    visitorWidget = new VisitorWidget(contentArea);
    media->accept(visitorWidget);

    // Aggiungi il widget all'area contenuto
    contentLayout->addWidget(visitorWidget->getWidget());
}

void BaseDetailPage::refreshDisplay() {
    clearContent();

    if (!currentMedia) return;

    // Aggiorna il titolo della pagina
    titleLabel->setText(QString::fromStdString(currentMedia->getTitolo()));

    // Ricrea il visitor widget con i dati aggiornati
    visitorWidget = new VisitorWidget(contentArea);
    currentMedia->accept(visitorWidget);

    // Aggiungi il widget all'area contenuto
    contentLayout->addWidget(visitorWidget->getWidget());
}

void BaseDetailPage::clearContent() {
    if (contentLayout) {
        QLayoutItem* item;
        while ((item = contentLayout->takeAt(0)) != nullptr) {
            if (item->widget()) item->widget()->deleteLater();
            delete item;
        }
    }

    if (visitorWidget) {
        visitorWidget->deleteLater();
        visitorWidget = nullptr;
    }
}

void BaseDetailPage::onBackClicked() {
    emit backRequested();
}



