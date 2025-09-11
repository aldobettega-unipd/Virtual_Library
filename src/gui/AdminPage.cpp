#include "AdminPage.h"
#include "../model/persistence/JsonManager.h"

#include <QList>
#include <QMessageBox>
#include <QFileDialog>

AdminPage::AdminPage(QWidget *parent) : BasePage(parent), addButton(nullptr), saveButton(nullptr), loadButton(nullptr)
{
    setupSpecificUI();
    setupSpecificConnections();
}

void AdminPage::setupSpecificUI() {
    QHBoxLayout* menuLayout = qobject_cast<QHBoxLayout*>(menuBar->layout());
    if (menuLayout) {
        addButton = new QPushButton("Aggiungi", this);
        saveButton = new QPushButton("Salva", this);
        loadButton = new QPushButton("Carica", this);

        QSize buttonSize(100, 30);
        addButton->setFixedSize(buttonSize);
        saveButton->setFixedSize(buttonSize);
        loadButton->setFixedSize(buttonSize);

        menuLayout->addWidget(addButton, 0, Qt::AlignRight);
        menuLayout->addWidget(saveButton, 0);
        menuLayout->addWidget(loadButton, 0);
    }
}

void AdminPage::setupSpecificConnections() {

    connect(addButton, &QPushButton::clicked, this, &AdminPage::onAddButtonClicked);
    connect(saveButton, &QPushButton::clicked, this, &AdminPage::onSaveButtonClicked);
    connect(loadButton, &QPushButton::clicked, this, &AdminPage::onLoadButtonClicked);

    connect(this, &AdminPage::onEditMedia, this, &AdminPage::handleEditMedia);
    connect(this, &AdminPage::onDeleteMedia, this, &AdminPage::handleDeleteMedia);

    connect(galleryWidget, &GalleryWidget::editMediaRequested, this, &AdminPage::handleEditMedia);
    connect(galleryWidget, &GalleryWidget::deleteMediaRequested, this, &AdminPage::handleDeleteMedia);
}

void AdminPage::onAddButtonClicked() {
    emit createNewObject(nullptr);
}

void AdminPage::handleEditMedia(Biblioteca* media) {
    // Implementa la modifica del media
    qDebug() << "Modifica media:" << QString::fromStdString(media->getTitolo());
}

void AdminPage::handleDeleteMedia(Biblioteca* media) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma eliminazione",
                                  "Sei sicuro di voler eliminare '" +
                                      QString::fromStdString(media->getTitolo()) + "'?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit removeObject(media);
    }
}

void AdminPage::onSaveButtonClicked() {
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Salva biblioteca",
        "biblioteca.json",
        "File JSON (*.json);;Tutti i file (*.*)"
        );

    if (!fileName.isEmpty()) {
        emit saveDataRequested(fileName);
    }
}

void AdminPage::onLoadButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Carica biblioteca",
        "",
        "File JSON (*.json);;Tutti i file (*.*)"
        );

    if (!fileName.isEmpty()) {
        emit loadDataRequested(fileName);
    }
}


