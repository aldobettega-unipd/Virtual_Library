// BaseEditWidget.cpp
#include "BaseEditWidget.h"
#include <QEnterEvent>

BaseEditWidget::BaseEditWidget(QWidget* parent)
    : QWidget(parent),
    titoloEdit(nullptr), annoPubblicazioneEdit(nullptr), idEdit(nullptr),
    genereEdit(nullptr), immagineLabel(nullptr), browseButton(nullptr),
    linguaEdit(nullptr), copieSpin(nullptr), numeroPagineEdit(nullptr),
    editoreEdit(nullptr), mainLayout(nullptr)
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(15);
}

void BaseEditWidget::createBibliotecaSection() {
    QWidget* bibliotecaSection = new QWidget(this);
    QFormLayout* bibliotecaLayout = new QFormLayout(bibliotecaSection);

    titoloEdit = new QLineEdit(bibliotecaSection);
    annoPubblicazioneEdit = new QLineEdit(bibliotecaSection);
    idEdit = new QLineEdit(bibliotecaSection);
    genereEdit = new QLineEdit(bibliotecaSection);
    linguaEdit = new QLineEdit(bibliotecaSection);

    copieSpin = new QSpinBox(bibliotecaSection);
    copieSpin->setRange(1, 1000);
    copieSpin->setValue(1);

    // Gestione immagine
    QWidget* imageWidget = new QWidget(bibliotecaSection);
    QHBoxLayout* imageLayout = new QHBoxLayout(imageWidget);
    imageLayout->setContentsMargins(0, 0, 0, 0);

    immagineLabel = new QLabel("Nessuna immagine selezionata", imageWidget);
    immagineLabel->setWordWrap(true);
    immagineLabel->setStyleSheet("QLabel {font-style: italic; }");

    browseButton = new QPushButton("Sfoglia...", imageWidget);
    browseButton->setMaximumWidth(100);

    imageLayout->addWidget(immagineLabel, 1);
    imageLayout->addWidget(browseButton);

    // layout
    bibliotecaLayout->addRow("Titolo*:", titoloEdit);
    bibliotecaLayout->addRow("Anno pubblicazione*:", annoPubblicazioneEdit);
    bibliotecaLayout->addRow("ID*:", idEdit);
    bibliotecaLayout->addRow("Genere*:", genereEdit);
    bibliotecaLayout->addRow("Immagine:", imageWidget);
    bibliotecaLayout->addRow("Lingua*:", linguaEdit);
    bibliotecaLayout->addRow("Numero copie*:", copieSpin);

    mainLayout->addWidget(bibliotecaSection);

    // Connetti il pulsante sfoglia
    connect(browseButton, &QPushButton::clicked, this, &BaseEditWidget::onBrowseImage);
}

void BaseEditWidget::createMultimediaSection() {
    QWidget* multimediaSection = new QWidget(this);
    QFormLayout* multimediaLayout = new QFormLayout(multimediaSection);

    supportoTecnoEdit = new QLineEdit(multimediaSection);
    casaDiProdEdit = new QLineEdit(multimediaSection);
    durataEdit = new QLineEdit(multimediaSection);

    multimediaLayout->addRow("Supporto tecnologico: ", supportoTecnoEdit);
    multimediaLayout->addRow("Casa di produzione: ", casaDiProdEdit);
    multimediaLayout->addRow("Durata (minuti): ", durataEdit);

    mainLayout->addWidget(multimediaSection);
}

void BaseEditWidget::createMediaCartaceoSection() {
    QWidget* cartaceoSection = new QWidget(this);
    QFormLayout* cartaceoLayout = new QFormLayout(cartaceoSection);

    numeroPagineEdit = new QLineEdit(cartaceoSection);
    editoreEdit = new QLineEdit(cartaceoSection);

    cartaceoLayout->addRow("Numero pagine*:", numeroPagineEdit);
    cartaceoLayout->addRow("Editore*:", editoreEdit);

    mainLayout->addWidget(cartaceoSection);
}

bool BaseEditWidget::validateBibliotecaFields() {
    if (!titoloEdit || titoloEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo Titolo è obbligatorio");
        return false;
    }

    if (!annoPubblicazioneEdit || annoPubblicazioneEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo Anno pubblicazione è obbligatorio");
        return false;
    }

    if (!idEdit || idEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo ID è obbligatorio");
        return false;
    }

    if (!genereEdit || genereEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo Genere è obbligatorio");
        return false;
    }

    if (!linguaEdit || linguaEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo Lingua è obbligatorio");
        return false;
    }

    return true;
}

bool BaseEditWidget::validateMultimediaFields() {
    // TO DO
    return true;
}

bool BaseEditWidget::validateMediaCartaceoFields() {
    if (!numeroPagineEdit || numeroPagineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo Numero pagine è obbligatorio");
        return false;
    }

    bool ok;
    int pagine = numeroPagineEdit->text().toInt(&ok);
    if (!ok || pagine <= 0) {
        QMessageBox::warning(nullptr, "Errore", "Il numero di pagine deve essere un numero positivo");
        return false;
    }

    if (!editoreEdit || editoreEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "Errore", "Il campo Editore è obbligatorio");
        return false;
    }

    return true;
}

void BaseEditWidget::populateBibliotecaFields(Biblioteca* media) {
    if (!media) return;

    if (titoloEdit) titoloEdit->setText(QString::fromStdString(media->getTitolo()));
    if (annoPubblicazioneEdit) annoPubblicazioneEdit->setText(QString::fromStdString(media->getAnnoPubblicazione()));
    if (idEdit) idEdit->setText(QString::fromStdString(media->getId()));
    if (genereEdit) genereEdit->setText(QString::fromStdString(media->getGenere()));
    if (linguaEdit) linguaEdit->setText(QString::fromStdString(media->getLingua()));
    if (copieSpin) copieSpin->setValue(media->getCopieTotali());

    // Gestione immagine
    QString imagePathStr = QString::fromStdString(media->getImmagine());
    if (!imagePathStr.isEmpty() && immagineLabel) {
        imagePath = imagePathStr;
        QFileInfo fileInfo(imagePathStr);
        immagineLabel->setText(fileInfo.fileName());
        immagineLabel->setStyleSheet("QLabel {font-style: italic; }");
        immagineLabel->setToolTip(imagePathStr);
    }
}

void BaseEditWidget::populateMultimediaFields(Multimedia* media) {
    if (!media) return;

    if (supportoTecnoEdit) supportoTecnoEdit->setText(QString::fromStdString(media->getSupportoTecnologico()));
    if (casaDiProdEdit) casaDiProdEdit->setText(QString::fromStdString(media->getCasaDiProduzione()));
    if (durataEdit) durataEdit->setText(QString::number(media->getDurata()));
}

void BaseEditWidget::populateMediaCartaceoFields(Media_cartaceo* media) {
    if (!media) return;

    if (numeroPagineEdit) numeroPagineEdit->setText(QString::number(media->getNumeroPagine()));
    if (editoreEdit) editoreEdit->setText(QString::fromStdString(media->getEditore()));
}

void BaseEditWidget::clearBibliotecaFields() {
    if (titoloEdit) titoloEdit->clear();
    if (annoPubblicazioneEdit) annoPubblicazioneEdit->clear();
    if (idEdit) idEdit->clear();
    if (genereEdit) genereEdit->clear();
    if (linguaEdit) linguaEdit->clear();
    if (copieSpin) copieSpin->setValue(1);

    // Reset immagine
    imagePath.clear();
    if (immagineLabel) {
        immagineLabel->setText("Nessuna immagine selezionata");
        immagineLabel->setToolTip("");
    }
}

void BaseEditWidget::clearMultimediaFields() {
    if (supportoTecnoEdit) supportoTecnoEdit->clear();
    if (casaDiProdEdit) casaDiProdEdit->clear();
    if (durataEdit) durataEdit->clear();
}

void BaseEditWidget::clearMediaCartaceoFields() {
    if (numeroPagineEdit) numeroPagineEdit->clear();
    if (editoreEdit) editoreEdit->clear();
}

void BaseEditWidget::onBrowseImage() {
    // Path delle risorse sempre relativo alla root del progetto
    QString resourcesPath = "./resources";

    QString fileName = QFileDialog::getOpenFileName(
        this, "Seleziona immagine", resourcesPath,
        "Immagini (*.png *.jpg *.jpeg *.bmp *.gif);;Tutti i file (*.*)");

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);

        // Salva solo il path relativo dalla root del progetto
        // Se il file è in ./resources/image.jpg, salva "resources/image.jpg"
        QDir projectDir(".");
        QString relativePath = projectDir.relativeFilePath(fileName);
        imagePath = relativePath;

        QString displayText = fileInfo.fileName();
        if (displayText.length() > 50) {
            displayText = "..." + displayText.right(47);
        }

        if (immagineLabel) {
            immagineLabel->setText(displayText);
            immagineLabel->setToolTip(relativePath);
        }

        qDebug() << "Selected image saved as relative path:" << relativePath;
    }
}

void BaseEditWidget::enterEvent(QEnterEvent* event) {
    QWidget::enterEvent(event);
}
