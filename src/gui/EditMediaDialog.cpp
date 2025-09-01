#include "EditMediaDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>

#include "../model/media/libro.h"
#include "../model/media/media_cartaceo.h"

EditMediaDialog::EditMediaDialog(Biblioteca* media, QWidget* parent)
    : QDialog(parent), mediaToEdit(media)
{
    // Initialize all pointers
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
    setWindowTitle("Modifica media");
    populateFields();
}

void EditMediaDialog::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Tipo media (non modificabile)
    mainLayout->addWidget(new QLabel("Tipo media:"));
    typeCombo = new QComboBox(this);

    // Determina il tipo dal media esistente e aggiungilo alla combo
    QString mediaType;
    if (dynamic_cast<Libro*>(mediaToEdit)) {
        mediaType = "Libro";
    }
    // Aggiungi qui altri tipi se necessario
    // else if (dynamic_cast<DVD*>(mediaToEdit)) { mediaType = "DVD"; }

    typeCombo->addItem(mediaType);
    typeCombo->setEnabled(false); // Disabilita il cambio tipo
    mainLayout->addWidget(typeCombo);

    // Stack per i form
    formStack = new QStackedWidget(this);
    mainLayout->addWidget(formStack);

    // Setup dei form specifici
    setupLibroForm();
    // Aggiungi qui setup per altri tipi se necessario

    // Imposta il form corretto in base al tipo
    if (mediaType == "Libro") {
        formStack->setCurrentIndex(0);
    }
    // Aggiungi qui altri tipi se necessario

    // Pulsanti
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Reset,
        this);
    mainLayout->addWidget(buttonBox);

    // Connessioni
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditMediaDialog::updateMedia);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::Reset), &QPushButton::clicked,
            this, &EditMediaDialog::onResetClicked);
    connect(browseButton, &QPushButton::clicked, this, &EditMediaDialog::onBrowseImage);
}

void EditMediaDialog::setupBibliotecaForm(QWidget* form)
{
    QFormLayout* layout = new QFormLayout(form);

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

    imageLayout->addWidget(immagineLabel, 1);
    imageLayout->addWidget(browseButton);

    layout->addRow("Titolo*:", titoloEdit);
    layout->addRow("Anno*:", annoPubblicazioneEdit);
    layout->addRow("Id*:", idEdit);
    layout->addRow("Genere*:", genereEdit);
    layout->addRow("Immagine:", imageWidget);
    layout->addRow("Lingua*:", linguaEdit);
    layout->addRow("Copie*:", copieSpin);
}

void EditMediaDialog::setupMediaCartaceoForm(QWidget* form)
{
    QFormLayout* layout = new QFormLayout(form);

    numeroPagineEdit = new QLineEdit(form);
    editoreEdit = new QLineEdit(form);

    layout->addRow("Numero Pagine*:", numeroPagineEdit);
    layout->addRow("Editore*:", editoreEdit);
}

void EditMediaDialog::setupLibroForm()
{
    libroForm = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(libroForm);

    // Form Biblioteca
    QWidget* bibliotecaWidget = new QWidget(libroForm);
    setupBibliotecaForm(bibliotecaWidget);

    // Form MediaCartaceo
    QWidget* cartaceoWidget = new QWidget(libroForm);
    setupMediaCartaceoForm(cartaceoWidget);

    // Form specifico Libro
    QWidget* specificWidget = new QWidget(libroForm);
    QFormLayout* specificLayout = new QFormLayout(specificWidget);
    autoreEdit = new QLineEdit(specificWidget);
    specificLayout->addRow("Autore*:", autoreEdit);

    mainLayout->addWidget(bibliotecaWidget);
    mainLayout->addWidget(cartaceoWidget);
    mainLayout->addWidget(specificWidget);
    mainLayout->addStretch();

    formStack->addWidget(libroForm);
}

void EditMediaDialog::populateFields()
{
    if (!mediaToEdit) return;

    // Compila i campi comuni a tutti i media
    titoloEdit->setText(QString::fromStdString(mediaToEdit->getTitolo()));
    annoPubblicazioneEdit->setText(QString::fromStdString(mediaToEdit->getAnnoPubblicazione()));
    idEdit->setText(QString::fromStdString(mediaToEdit->getId()));
    genereEdit->setText(QString::fromStdString(mediaToEdit->getGenere()));
    linguaEdit->setText(QString::fromStdString(mediaToEdit->getLingua()));
    copieSpin->setValue(mediaToEdit->getCopieTotali());

    QString imagePathStr = QString::fromStdString(mediaToEdit->getImmagine());
    if (!imagePathStr.isEmpty()) {
        imagePath = imagePathStr;
        QFileInfo fileInfo(imagePathStr);
        immagineLabel->setText(fileInfo.fileName());
        immagineLabel->setStyleSheet("QLabel { color: black; font-style: normal; }");
        immagineLabel->setToolTip(imagePathStr);
    }

    if (Media_cartaceo* cartaceo = dynamic_cast<Media_cartaceo*>(mediaToEdit)) {
        numeroPagineEdit->setText(QString::number(cartaceo->getNumeroPagine()));
        editoreEdit->setText(QString::fromStdString(cartaceo->getEditore()));
    }

    if (Libro* libro = dynamic_cast<Libro*>(mediaToEdit)) {
        autoreEdit->setText(QString::fromStdString(libro->getAutore()));
    }
}

bool EditMediaDialog::validateFields() const
{
    // Validazione campi obbligatori
    if (titoloEdit->text().isEmpty() ||
        annoPubblicazioneEdit->text().isEmpty() ||
        idEdit->text().isEmpty() ||
        genereEdit->text().isEmpty() ||
        linguaEdit->text().isEmpty() ||
        numeroPagineEdit->text().isEmpty() ||
        editoreEdit->text().isEmpty() ||
        autoreEdit->text().isEmpty()) {
        QMessageBox::warning(const_cast<EditMediaDialog*>(this),
                             "Campi mancanti",
                             "Compila tutti i campi obbligatori (*)");
        return false;
    }

    // Validazione numero pagine
    bool conversionOk;
    int numeroPagine = numeroPagineEdit->text().toInt(&conversionOk);
    if (!conversionOk || numeroPagine <= 0) {
        QMessageBox::warning(const_cast<EditMediaDialog*>(this),
                             "Errore",
                             "Numero pagine non valido");
        return false;
    }

    return true;
}

void EditMediaDialog::updateMedia()
{
    if (!mediaToEdit || !validateFields()) {
        return;
    }

    try {
        // Aggiorna i campi comuni
        mediaToEdit->setTitolo(titoloEdit->text().toStdString());
        mediaToEdit->setAnnoPubblicazione(annoPubblicazioneEdit->text().toStdString());
        mediaToEdit->setId(idEdit->text().toStdString());
        mediaToEdit->setGenere(genereEdit->text().toStdString());
        mediaToEdit->setImmagine(imagePath.toStdString());
        mediaToEdit->setLingua(linguaEdit->text().toStdString());
        mediaToEdit->setCopieTotali(copieSpin->value());

        // Aggiorna i campi specifici
        if (Media_cartaceo* cartaceo = dynamic_cast<Media_cartaceo*>(mediaToEdit)) {
            bool ok;
            int numeroPagine = numeroPagineEdit->text().toInt(&ok);
            if (ok) {
                cartaceo->setNumeroPagine(numeroPagine);
            }
            cartaceo->setEditore(editoreEdit->text().toStdString());
        }

        if (Libro* libro = dynamic_cast<Libro*>(mediaToEdit)) {
            libro->setAutore(autoreEdit->text().toStdString());
        }

        accept(); // Chiudi il dialog con successo

    } catch (const std::exception& e) {
        QMessageBox::critical(this,
                              "Errore",
                              QString("Errore nell'aggiornamento: %1").arg(e.what()));
    }
}

void EditMediaDialog::onBrowseImage()
{
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
        QFileInfo fileInfo(fileName);
        QString displayText = fileInfo.fileName();

        if (fileName.length() > 50) {
            displayText = "..." + fileName.right(47);
        }

        immagineLabel->setText(displayText);
        immagineLabel->setToolTip(fileName);
        immagineLabel->setStyleSheet("QLabel { color: black; font-style: normal; }");
    }
}

void EditMediaDialog::onResetClicked()
{
    populateFields(); // Ripristina i valori originali
}
