#include "AdminDetailPage.h"
#include <QDebug>
#include <QMessageBox>

#include "../model/media/biblioteca.h"

AdminDetailPage::AdminDetailPage(QWidget* parent) : BaseDetailPage(parent), editButton(nullptr), deleteButton(nullptr) {
    setupSpecificUI();
    setupSpecificConnections();
}

void AdminDetailPage::setupSpecificUI() {
    editButton = new QPushButton("Edit", this);
    deleteButton = new QPushButton("Delete", this);

    headerLayout->addWidget(editButton);
    headerLayout->addWidget(deleteButton);

}

void AdminDetailPage::setupSpecificConnections() {
    connect(editButton, &QPushButton::clicked, this, &AdminDetailPage::onEditClicked);
    connect(deleteButton, &QPushButton::clicked, this, &AdminDetailPage::onDeleteClicked);
}

void AdminDetailPage::onEditClicked() {
    if (!currentMedia) return;

    emit editRequested(currentMedia);
}

void AdminDetailPage::onDeleteClicked() {
    if (!currentMedia) {
        qWarning() << "Nessun media selezionato per l'eliminazione";
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Conferma eliminazione",
        QString("Sei sicuro di voler eliminare definitivamente:\n"
                "'%1'?\n\n"
                "Questa operazione non può essere annullata.")
            .arg(QString::fromStdString(currentMedia->getTitolo())),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No  // Default button
        );

    if (reply == QMessageBox::Yes) {
        qDebug() << "Eliminazione confermata per:" << QString::fromStdString(currentMedia->getTitolo());
        emit deleteRequested(currentMedia);
        emit backRequested();
    } else {
        qDebug() << "Eliminazione annullata";
    }
}
