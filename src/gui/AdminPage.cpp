#include "AdminPage.h"
#include "../model/persistence/JsonManager.h"
#include "MediaDialog.h"

#include <QList>
#include <QMessageBox>

AdminPage::AdminPage(QWidget *parent) : BasePage(parent), addButton(nullptr)
{
    setupSpecificUI();
    setupSpecificConnections();
}

void AdminPage::setupSpecificUI() {
    QHBoxLayout* menuLayout = qobject_cast<QHBoxLayout*>(menuBar->layout());
    if (menuLayout) {
        addButton = new QPushButton("Aggiungi", this);
        menuLayout->insertWidget(0, addButton, 0, Qt::AlignLeft);
    }

    setStyleSheet("AdminPage { background-color: #fff3cd; }");
}

void AdminPage::setupSpecificConnections() {

    connect(addButton, &QPushButton::clicked, this, &AdminPage::onAddButtonClicked);

    connect(this, &AdminPage::onEditMedia, this, &AdminPage::handleEditMedia);
    connect(this, &AdminPage::onDeleteMedia, this, &AdminPage::handleDeleteMedia);

    connect(galleryWidget, &GalleryWidget::editMediaRequested, this, &AdminPage::handleEditMedia);
    connect(galleryWidget, &GalleryWidget::deleteMediaRequested, this, &AdminPage::handleDeleteMedia);
}

void AdminPage::onAddButtonClicked() {

    MediaDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Biblioteca* newMedia = dialog.createMedia();
        if(newMedia) {
            try {
                if (newMedia->getTitolo().empty() || newMedia->getId().empty()) {
                    QMessageBox::warning(this, "Errore", "Dati obbligatori mancanti");
                    delete newMedia;
                    return;
                }
                emit createNewObject(newMedia);
                QMessageBox::information(this, "Successo", "Media aggiunto con successo");
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Errore", QString("Errore nel salvataggio: %1").arg(e.what()));
                delete newMedia;
            }
        } else {
            QMessageBox::warning(this, "Errore", "Tipo di media non supportatp");
        }
    }

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


