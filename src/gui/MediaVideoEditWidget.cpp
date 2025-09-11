#include "MediaVideoEditWidget.h"

MediaVideoEditWidget::MediaVideoEditWidget(QWidget* parent)
    : BaseEditWidget(parent), registaEdit(nullptr)
{
    setupUI();
}

void MediaVideoEditWidget::setupUI() {
    createBibliotecaSection();
    createMultimediaSection();

    QWidget* videoSection = new QWidget(this);
    QFormLayout* videoLayout = new QFormLayout(videoSection);

    registaEdit = new QLineEdit(videoSection);

    videoLayout->addRow("Regista*:", registaEdit);

    mainLayout->addWidget(videoSection);
    mainLayout->addStretch();
}

void MediaVideoEditWidget::setMedia(Biblioteca* media) {
    currentMediaVideo = dynamic_cast<Media_video*>(media);

    if (currentMediaVideo) {
        populateBibliotecaFields(currentMediaVideo);
        populateMultimediaFields(currentMediaVideo);
        populateMediaVideoFields(currentMediaVideo);
    } else {
        clearFields();
    }
}

Biblioteca* MediaVideoEditWidget::createMedia() {
    if (!validateFields())
        return nullptr;

    try {
        return new Media_video(
            titoloEdit->text().toStdString(),
            annoPubblicazioneEdit->text().toStdString(),
            idEdit->text().toStdString(),
            genereEdit->text().toStdString(),
            imagePath.toStdString(),
            linguaEdit->text().toStdString(),
            copieSpin->value(),
            supportoTecnoEdit->text().toStdString(),
            casaDiProdEdit->text().toStdString(),
            durataEdit->text().toInt(),
            registaEdit->text().toStdString()
            );
    } catch (const std::exception& e) {
        QMessageBox::critical(const_cast<MediaVideoEditWidget*>(this), "Errore",
                              QString("Errore nella creazione del Media video: %1").arg(e.what()));
        return nullptr;
    }
}

void MediaVideoEditWidget::updateMedia() {
    if (!currentMediaVideo || !validateFields())
        return;

    try {
        currentMediaVideo->setTitolo(titoloEdit->text().toStdString());
        currentMediaVideo->setAnnoPubblicazione(annoPubblicazioneEdit->text().toStdString());
        currentMediaVideo->setId(idEdit->text().toStdString());
        currentMediaVideo->setGenere(genereEdit->text().toStdString());
        currentMediaVideo->setImmagine(imagePath.toStdString());
        currentMediaVideo->setLingua(linguaEdit->text().toStdString());
        currentMediaVideo->setCopieTotali(copieSpin->value());
        currentMediaVideo->setSupportoTecnologico(supportoTecnoEdit->text().toStdString());
        currentMediaVideo->setCasaDiProduzione(casaDiProdEdit->text().toStdString());
        currentMediaVideo->setDurata(durataEdit->text().toInt());
        currentMediaVideo->setRegista(registaEdit->text().toStdString());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore", QString("Errore nell'aggiornamento del Media video: %1").arg(e.what()));
    }
}

void MediaVideoEditWidget::clearFields() {
    clearBibliotecaFields();
    clearMultimediaFields();
    clearMediaVideoFields();
    currentMediaVideo = nullptr;
}

bool MediaVideoEditWidget::validateFields() {
    if (!validateBibliotecaFields() || !validateMultimediaFields() || !validateMediaVideoFields())
        return false;
    return true;
}

void MediaVideoEditWidget::populateMediaVideoFields(Media_video* video) {
    registaEdit->setText(QString::fromStdString(video->getRegista()));
}

void MediaVideoEditWidget::clearMediaVideoFields() {
    if (registaEdit)
        registaEdit->clear();
}

bool MediaVideoEditWidget::validateMediaVideoFields() {
    if (!registaEdit || registaEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Il campo regista è obbligatorio");
        return false;
    }
    return true;
}
