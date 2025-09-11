// MediaEditManager.cpp
#include "MediaEditManager.h"
#include "../model/media/libro.h"
#include "../model/media/periodico.h"
#include <QDebug>

MediaEditManager::MediaEditManager(QWidget* parent)
    : QWidget(parent), currentMode(CREATE_MODE), mediaBeingEdited(nullptr),
    unsavedChanges(false), mainLayout(nullptr), titleLabel(nullptr),
    typeSelectionWidget(nullptr), typeComboBox(nullptr), editStack(nullptr),
    videoWidget(nullptr), periodicoWidget(nullptr), libroWidget(nullptr), buttonWidget(nullptr),
    saveButton(nullptr), cancelButton(nullptr), backButton(nullptr)
{
    setupUI();
    setupConnections();
    enterCreateMode();
}

void MediaEditManager::setupUI() {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // Titolo
    titleLabel = new QLabel(this);
    titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; color: #2c3e50; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Separatore
    QFrame* separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("QFrame { color: #bdc3c7; }");
    mainLayout->addWidget(separator);

    // Widget per selezione tipo (visibile solo in CREATE_MODE)
    typeSelectionWidget = new QWidget(this);
    QHBoxLayout* typeLayout = new QHBoxLayout(typeSelectionWidget);
    typeLayout->setContentsMargins(0, 0, 0, 0);

    QLabel* typeLabel = new QLabel("Tipo di media:", typeSelectionWidget);
    typeLabel->setStyleSheet("QLabel { font-weight: bold; }");

    typeComboBox = new QComboBox(typeSelectionWidget);
    typeComboBox->addItems({"Media video", "Periodico", "Libro", "Cd"});
    typeComboBox->setMinimumWidth(150);

    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(typeComboBox);
    typeLayout->addStretch();

    mainLayout->addWidget(typeSelectionWidget);

    // Stack dei widget di modifica
    editStack = new QStackedWidget(this);

    // Crea i widget specifici per ogni tipo
    videoWidget = new MediaVideoEditWidget(this);    // index 0
    periodicoWidget = new PeriodicoEditWidget(this); // index 1
    libroWidget = new LibroEditWidget(this);         // index 2
    cdWidget = new CdEditWidget(this);               // index 3


    editStack->addWidget(videoWidget);      // index 0
    editStack->addWidget(periodicoWidget);  // index 1
    editStack->addWidget(libroWidget);      // index 2
    editStack->addWidget(cdWidget);         // index 3


    mainLayout->addWidget(editStack);

    // Widget bottoni
    buttonWidget = new QWidget(this);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(0, 10, 0, 0);

    backButton = new QPushButton("← Indietro", buttonWidget);
    backButton->setStyleSheet("QPushButton { background-color: #95a5a6; color: white; border: none; padding: 8px 16px; border-radius: 4px; } QPushButton:hover { background-color: #7f8c8d; }");

    cancelButton = new QPushButton("Annulla", buttonWidget);
    cancelButton->setStyleSheet("QPushButton { background-color: #e74c3c; color: white; border: none; padding: 8px 16px; border-radius: 4px; } QPushButton:hover { background-color: #c0392b; }");

    saveButton = new QPushButton("Salva", buttonWidget);
    saveButton->setStyleSheet("QPushButton { background-color: #27ae60; color: white; border: none; padding: 8px 16px; border-radius: 4px; } QPushButton:hover { background-color: #229954; }");
    saveButton->setDefault(true);

    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(saveButton);

    mainLayout->addWidget(buttonWidget);
}

void MediaEditManager::setupConnections() {
    // Connessioni per la selezione del tipo
    connect(typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MediaEditManager::onMediaTypeChanged);

    // Connessioni per i bottoni
    connect(saveButton, &QPushButton::clicked, this, &MediaEditManager::onSaveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &MediaEditManager::onCancelClicked);
    connect(backButton, &QPushButton::clicked, this, &MediaEditManager::onBackClicked);
}

void MediaEditManager::enterCreateMode() {
    currentMode = CREATE_MODE;
    mediaBeingEdited = nullptr;
    unsavedChanges = false;

    // Mostra il widget di selezione tipo
    typeSelectionWidget->setVisible(true);
    typeComboBox->setCurrentIndex(2);

    // Pulisci tutti i widget
    videoWidget->clearFields();
    periodicoWidget->clearFields();
    libroWidget->clearFields();
    cdWidget->clearFields();

    updateUIForMode();
    setCurrentEditWidget(2); // Inizia con Libro
}

void MediaEditManager::enterEditMode(Biblioteca* media) {
    if (!media) {
        qWarning() << "Tentativo di entrare in modalità edit con media nullo";
        return;
    }

    currentMode = EDIT_MODE;
    mediaBeingEdited = media;
    unsavedChanges = false;

    // Nascondi il widget di selezione tipo
    typeSelectionWidget->setVisible(false);

    // Determina il tipo di media e imposta il widget corretto
    int typeIndex = getMediaTypeIndex(media);
    setCurrentEditWidget(typeIndex);

    // Popola i campi con i dati del media
    BaseEditWidget* currentWidget = getCurrentEditWidget();
    if (currentWidget) {
        currentWidget->setMedia(media);
    }

    updateUIForMode();
}

void MediaEditManager::onMediaTypeChanged(int index) {
    if (currentMode == CREATE_MODE) {
        if (!confirmDiscardChanges()) {
            // Ripristina la selezione precedente
            typeComboBox->blockSignals(true);
            typeComboBox->setCurrentIndex(editStack->currentIndex());
            typeComboBox->blockSignals(false);
            return;
        }

        setCurrentEditWidget(index);
        resetToCleanState();
    }
}

void MediaEditManager::onSaveClicked() {
    BaseEditWidget* currentWidget = getCurrentEditWidget();
    if (!currentWidget) {
        qWarning() << "Nessun widget corrente disponibile per il salvataggio";
        return;
    }

    if (currentMode == CREATE_MODE) {
        // Modalità creazione
        Biblioteca* newMedia = currentWidget->createMedia();
        if (newMedia) {
            resetToCleanState();
            emit mediaCreated(newMedia);
        }
    } else if (currentMode == EDIT_MODE) {
        // Modalità modifica
        currentWidget->updateMedia();
        if (mediaBeingEdited) {
            resetToCleanState();
            emit mediaUpdated(mediaBeingEdited);
        }
    }
}

void MediaEditManager::onCancelClicked() {
    if (!confirmDiscardChanges()) {
        return;
    }

    resetToCleanState();
    emit operationCancelled();
}

void MediaEditManager::onBackClicked() {
    if (!confirmDiscardChanges()) {
        return;
    }

    resetToCleanState();
    emit backRequested();
}

void MediaEditManager::updateUIForMode() {
    updateTitle();

    if (currentMode == CREATE_MODE) {
        saveButton->setText("Crea");
        backButton->setVisible(true);
        cancelButton->setText("Annulla");
    } else {
        saveButton->setText("Salva modifiche");
        backButton->setVisible(true);
        cancelButton->setText("Annulla modifiche");
    }
}

void MediaEditManager::setCurrentEditWidget(int index) {
    if (index >= 0 && index < editStack->count()) {
        editStack->setCurrentIndex(index);
    }
}

BaseEditWidget* MediaEditManager::getCurrentEditWidget() const {
    return qobject_cast<BaseEditWidget*>(editStack->currentWidget());
}

int MediaEditManager::getMediaTypeIndex(Biblioteca* media) const {
    if (dynamic_cast<Media_video*>(media)) {
        return 0;
    } else if (dynamic_cast<Periodico*>(media)) {
        return 1;
    } else if (dynamic_cast<Libro*>(media)) {
        return 2;
    } else if (dynamic_cast<Cd*>(media)) {
        return 3;
    }

    return 2; // Default a Libro
}

void MediaEditManager::updateTitle() {
    QString title;
    if (currentMode == CREATE_MODE) {
        title = "Crea nuovo media";
    } else {
        title = "Modifica media";
        if (mediaBeingEdited) {
            title += QString(" - %1").arg(QString::fromStdString(mediaBeingEdited->getTitolo()));
        }
    }
    titleLabel->setText(title);
}

void MediaEditManager::resetToCleanState() {
    unsavedChanges = false;
    saveButton->setText(currentMode == CREATE_MODE ? "Crea" : "Salva modifiche");
}

bool MediaEditManager::confirmDiscardChanges() {
    if (!unsavedChanges) {
        return true;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Modifiche non salvate",
        "Ci sono modifiche non salvate. Vuoi continuare senza salvare?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
        );

    return reply == QMessageBox::Yes;
}
