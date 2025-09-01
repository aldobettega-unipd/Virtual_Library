#include "MediaDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDebug>
#include <QDir>
#include <QFileDialog>

#include "../model/media/libro.h"

MediaDialog::MediaDialog(QWidget* parent) : QDialog(parent) {
    // Initialize all pointers to nullptr
    titoloEdit = nullptr;
    annoPubblicazioneEdit = nullptr;
    idEdit = nullptr;
    genereEdit = nullptr;
    immagineLabel = nullptr;
    browseButton = nullptr;
    linguaEdit = nullptr;
    copieSpin = nullptr;
    numeroPagineEdit = nullptr;
    editoreEdit = nullptr;
    autoreEdit = nullptr;

    setupUI();
    setWindowTitle("Aggiungi nuovo media");
}

void MediaDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Tipo media
    mainLayout->addWidget(new QLabel("Tipo media:"));
    typeCombo = new QComboBox(this);
    typeCombo->addItems({"Libro"});
    mainLayout->addWidget(typeCombo);

    // Stack per i form
    formStack = new QStackedWidget(this);
    mainLayout->addWidget(formStack);

    // Setup dei form
    setupLibroForm();

    // Pulsanti
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    mainLayout->addWidget(buttonBox);

    // Connessioni
    connect(typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MediaDialog::onMediaTypeChanged);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void MediaDialog::setupBibliotecaForm(QWidget* form) {
    QFormLayout* layout = new QFormLayout(form); // Create layout if it doesn't exist

    titoloEdit = new QLineEdit(form);
    annoPubblicazioneEdit = new QLineEdit(form);
    idEdit = new QLineEdit(form);
    genereEdit = new QLineEdit(form);
    linguaEdit = new QLineEdit(form);
    copieSpin = new QSpinBox(form);
    copieSpin->setRange(1, 100);

    QWidget* imageWidget = new QWidget(form);
    QHBoxLayout* imageLayout = new QHBoxLayout(imageWidget);
    imageLayout->setContentsMargins(0, 0, 0, 0);

    immagineLabel = new QLabel("nessuna immagine selezionata", form);
    immagineLabel->setWordWrap(true);
    immagineLabel->setStyleSheet("QLabel { color: #666; font-style: italic; }");
    browseButton = new QPushButton("Sfoglia...", form);

    imageLayout->addWidget(immagineLabel ,1);
    imageLayout->addWidget(browseButton);

    connect(browseButton, &QPushButton::clicked, this, &MediaDialog::onBrowseImage);

    layout->addRow("Titolo*:", titoloEdit);
    layout->addRow("Anno*:", annoPubblicazioneEdit);
    layout->addRow("Id*:", idEdit);
    layout->addRow("Genere*:", genereEdit);
    layout->addRow("Immagine:", imageWidget);
    layout->addRow("Lingua*:", linguaEdit);
    layout->addRow("Copie*:", copieSpin);
}

void MediaDialog::onBrowseImage() {
    QString resourcesPath = QDir::currentPath() + "/resources";
    QDir resourcesDir(resourcesPath);

    QString startPath = resourcesDir.exists() ? resourcesPath : resourcesPath;

    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Seleziona immagine",
        startPath,
        "Immagini (*.png *.jpg *.jpeg *.bmp *.gif);;Tutti i file (*.*)"
        );

    if (!fileName.isEmpty()) {
        imagePath = fileName;

        // Mostra solo il nome del file per brevità, o il percorso abbreviato
        QFileInfo fileInfo(fileName);
        QString displayText = fileInfo.fileName();

        // Se il percorso è molto lungo, mostra solo il nome file
        if (fileName.length() > 50) {
            displayText = "..." + fileName.right(47);
        }

        immagineLabel->setText(displayText);
        immagineLabel->setToolTip(fileName);  // Tooltip con il percorso completo
        immagineLabel->setStyleSheet("QLabel { color: black; font-style: normal; }");
    }
}

void MediaDialog::setupMediaCartaceoForm(QWidget* form) {
    QFormLayout* layout = new QFormLayout(form);

    numeroPagineEdit = new QLineEdit(form);
    editoreEdit = new QLineEdit(form);

    layout->addRow("Numero Pagine*:", numeroPagineEdit);
    layout->addRow("Editore:*", editoreEdit);
}

void MediaDialog::setupLibroForm() {
    libroForm = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(libroForm);

    QWidget* bibliotecaWidget = new QWidget(libroForm);
    setupBibliotecaForm(bibliotecaWidget);

    QWidget* cartaceoWidget = new QWidget(libroForm);
    setupMediaCartaceoForm(cartaceoWidget);

    QWidget* specificWidget = new QWidget(libroForm);
    QFormLayout* specificLayout = new QFormLayout(specificWidget);
    autoreEdit = new QLineEdit(specificWidget);
    specificLayout->addRow("Autore:*", autoreEdit);

    mainLayout->addWidget(bibliotecaWidget);
    mainLayout->addWidget(cartaceoWidget);
    mainLayout->addWidget(specificWidget);
    mainLayout->addStretch();

    formStack->addWidget(libroForm);
}

Biblioteca* MediaDialog::createMedia() const {
    // Add input validation
    if (titoloEdit->text().isEmpty() ||
        annoPubblicazioneEdit->text().isEmpty() ||
        idEdit->text().isEmpty() ||
        genereEdit->text().isEmpty() ||
        linguaEdit->text().isEmpty() ||
        numeroPagineEdit->text().isEmpty() ||
        editoreEdit->text().isEmpty() ||
        autoreEdit->text().isEmpty()) {
        return nullptr;
    }

    // Conversione numero pagine
    bool conversionOk;
    int numeroPagine = numeroPagineEdit->text().toInt(&conversionOk);
    if (!conversionOk || numeroPagine <= 0) {
        qWarning() << "Numero pagine non valido";
        return nullptr;
    }

    QString tipo = typeCombo->currentText();

    if (tipo == "Libro") {
        try {
            return new Libro(
                titoloEdit->text().toStdString(),
                annoPubblicazioneEdit->text().toStdString(),
                idEdit->text().toStdString(),
                genereEdit->text().toStdString(),
                imagePath.toStdString(),
                linguaEdit->text().toStdString(),
                copieSpin->value(),
                numeroPagine,
                editoreEdit->text().toStdString(),
                autoreEdit->text().toStdString()
                );
        } catch (const std::exception& e) {
            qCritical() << "Errore nella creazione del libro:" << e.what();
            return nullptr;
        }
    }

    qWarning() << "Tipo media non supportato:" << tipo;
    return nullptr;
}

void MediaDialog::clearFields() {
    if (titoloEdit) titoloEdit->clear();
    if (annoPubblicazioneEdit) annoPubblicazioneEdit->clear();
    if (idEdit) idEdit->clear();
    if (genereEdit) genereEdit->clear();
    if (immagineLabel) {
        immagineLabel->setText("Nessuna immagine selezionata");
        immagineLabel->setStyleSheet("QLabel { color: #666; font-style: italic; }");
        immagineLabel->setToolTip("");
    }
    imagePath = "";  // Resetta il percorso
    if (linguaEdit) linguaEdit->clear();
    if (copieSpin) copieSpin->setValue(1);
    if (numeroPagineEdit) numeroPagineEdit->clear();
    if (editoreEdit) editoreEdit->clear();
    if (autoreEdit) autoreEdit->clear();
}

void MediaDialog::onMediaTypeChanged(int index) {
    formStack->setCurrentIndex(index);
    clearFields();
}
