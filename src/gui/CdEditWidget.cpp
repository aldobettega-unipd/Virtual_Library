#include "CdEditWidget.h"

CdEditWidget::CdEditWidget(QWidget* parent)
    : BaseEditWidget(parent), artistaEdit(nullptr), nTracceEdit(nullptr)
{
    setupUI();
}

void CdEditWidget::setupUI() {
    createBibliotecaSection();
    createMultimediaSection();

    QWidget* cdSection = new QWidget(this);
    QFormLayout* cdLayout = new QFormLayout(cdSection);

    artistaEdit = new QLineEdit(cdSection);
    nTracceEdit = new QLineEdit(cdSection);

    cdLayout->addRow("Arstista*:", artistaEdit);
    cdLayout->addRow("Numero tracce:*", nTracceEdit);

    mainLayout->addWidget(cdSection);
    mainLayout->addStretch();
}

void CdEditWidget::setMedia(Biblioteca* media) {
    currentCd = dynamic_cast<Cd*>(media);

    if (currentCd) {
        populateBibliotecaFields(currentCd);
        populateMultimediaFields(currentCd);
        populateCdFields(currentCd);
    } else {
        clearFields();
    }
}

Biblioteca* CdEditWidget::createMedia() {
    if (!validateFields())
        return nullptr;

    try {
        return new Cd(
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
            artistaEdit->text().toStdString(),
            nTracceEdit->text().toInt()
            );
    } catch (const std::exception& e) {
        QMessageBox::critical(const_cast<CdEditWidget*>(this), "Errore",
                              QString("Errore nella creazione del cd: %1").arg(e.what()));
        return nullptr;
    }
}

void CdEditWidget::updateMedia() {
    if (!currentCd || !validateFields())
        return;

    try {
        currentCd->setTitolo(titoloEdit->text().toStdString());
        currentCd->setAnnoPubblicazione(annoPubblicazioneEdit->text().toStdString());
        currentCd->setId(idEdit->text().toStdString());
        currentCd->setGenere(genereEdit->text().toStdString());
        currentCd->setImmagine(imagePath.toStdString());
        currentCd->setLingua(linguaEdit->text().toStdString());
        currentCd->setCopieTotali(copieSpin->value());
        currentCd->setSupportoTecnologico(supportoTecnoEdit->text().toStdString());
        currentCd->setCasaDiProduzione(casaDiProdEdit->text().toStdString());
        currentCd->setDurata(durataEdit->text().toInt());
        currentCd->setArtista(artistaEdit->text().toStdString());
        currentCd->setNumeroTracce(nTracceEdit->text().toInt());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore", QString("Errore nell'aggiornamento del cd: %1").arg(e.what()));
    }
}

void CdEditWidget::clearFields() {
    clearBibliotecaFields();
    clearMultimediaFields();
    clearCdFields();
    currentCd = nullptr;
}

bool CdEditWidget::validateFields() {
    if (!validateBibliotecaFields() || !validateMultimediaFields() || !validateCdFields())
        return false;
    return true;
}

void CdEditWidget::populateCdFields(Cd* cd) {
    artistaEdit->setText(QString::fromStdString(cd->getArtista()));
    nTracceEdit->setText(QString::number(cd->getNumeroTracce()));
}

void CdEditWidget::clearCdFields() {
    if (artistaEdit)
        artistaEdit->clear();
    if (nTracceEdit)
        nTracceEdit->clear();
}

bool CdEditWidget::validateCdFields() {
    if (!artistaEdit || artistaEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Il campo artista è obbligatorio");
        return false;
    }
    if (!nTracceEdit || nTracceEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Il campo numero tracce è obbligatorio");
        return false;
    }
    return true;
}
