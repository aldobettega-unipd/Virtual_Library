#include "PeriodicoEditWidget.h"
#include <QDebug>

PeriodicoEditWidget::PeriodicoEditWidget(QWidget* parent)
    : BaseEditWidget(parent), periodoBox(nullptr), diffusioneBox(nullptr), numeroArticoliEdit(nullptr), dataEdit(nullptr)
{
    setupUI();
}

void PeriodicoEditWidget::setupUI() {
    createBibliotecaSection();
    createMediaCartaceoSection();

    QWidget* periodicoSection = new QWidget(this);
    QFormLayout* periodicoLayout = new QFormLayout(periodicoSection);

    periodoBox = new QComboBox(periodicoSection);
    periodoBox->addItems({"Giornaliero", "Settimanale", "Mensile", "Annuale"});
    diffusioneBox = new QComboBox(periodicoSection);
    diffusioneBox->addItems({"Provinciale", "Regionale", "Nazionale", "Internazionale"});
    numeroArticoliEdit = new QLineEdit(periodicoSection);
    dataEdit = new QDateEdit(periodicoSection);

    periodicoLayout->addRow("Periodo*:", periodoBox);
    periodicoLayout->addRow("Diffusione*:", diffusioneBox);
    periodicoLayout->addRow("Numero articoli*:", numeroArticoliEdit);
    periodicoLayout->addRow("Data*:", dataEdit);

    mainLayout->addWidget(periodicoSection);
    mainLayout->addStretch();
}

void PeriodicoEditWidget::setMedia(Biblioteca* media) {
    currentPeriodico = dynamic_cast<Periodico*>(media);

    if (currentPeriodico) {
        populateBibliotecaFields(currentPeriodico);
        populateMediaCartaceoFields(currentPeriodico);
        populatePeriodicoFields(currentPeriodico);
    } else {
        clearFields();
    }
}

Biblioteca* PeriodicoEditWidget::createMedia() {
    if (!validateFields())
        return nullptr;

    try {
        return new Periodico(
            titoloEdit->text().toStdString(),
            annoPubblicazioneEdit->text().toStdString(),
            idEdit->text().toStdString(),
            genereEdit->text().toStdString(),
            imagePath.toStdString(),
            linguaEdit->text().toStdString(),
            copieSpin->value(),
            numeroPagineEdit->text().toInt(),
            editoreEdit->text().toStdString(),
            Periodico::stringToPeriodo(periodoBox->currentText().toStdString()),
            Periodico::stringToDiffusione(diffusioneBox->currentText().toStdString()),
            numeroArticoliEdit->text().toInt(),
            dataEdit->date().toString("dd/MM/yyyy").toStdString()
            );
    } catch (const std::exception& e) {
        QMessageBox::critical(const_cast<PeriodicoEditWidget*>(this), "Errore",
                              QString("Errore nella creazione del periodico: %1").arg(e.what()));
        return nullptr;
    }
}

void PeriodicoEditWidget::updateMedia() {
    if (!currentPeriodico || !validateFields())
        return;

    try {
        currentPeriodico->setTitolo(titoloEdit->text().toStdString());
        currentPeriodico->setAnnoPubblicazione(annoPubblicazioneEdit->text().toStdString());
        currentPeriodico->setId(idEdit->text().toStdString());
        currentPeriodico->setGenere(genereEdit->text().toStdString());
        currentPeriodico->setImmagine(imagePath.toStdString());
        currentPeriodico->setLingua(linguaEdit->text().toStdString());
        currentPeriodico->setCopieTotali(copieSpin->value());
        currentPeriodico->setNumeroPagine(numeroPagineEdit->text().toInt());
        currentPeriodico->setEditore(editoreEdit->text().toStdString());
        currentPeriodico->setPeriodo(Periodico::stringToPeriodo(periodoBox->currentText().toStdString()));
        currentPeriodico->setDiffusione(Periodico::stringToDiffusione(diffusioneBox->currentText().toStdString()));
        currentPeriodico->setData(dataEdit->date().toString("dd/MM/yyyy").toStdString());

        qDebug() << "Periodico aggiornato con successo:" << QString::fromStdString(currentPeriodico->getTitolo());

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore", QString("Errore nell'aggiornamento del Periodico: %1").arg(e.what()));
    }
}

void PeriodicoEditWidget::clearFields() {
    clearBibliotecaFields();
    clearMediaCartaceoFields();
    clearPeriodicoFields();
    currentPeriodico = nullptr;
}

bool PeriodicoEditWidget::validateFields() {
    if (!validateBibliotecaFields() || !validateMediaCartaceoFields()) {
        return false;
    }
    return true;
}

void PeriodicoEditWidget::populatePeriodicoFields(Periodico* periodico) {
    periodoBox->setCurrentText(QString::fromStdString(periodico->periodoToString()));
    diffusioneBox->setCurrentText(QString::fromStdString(periodico->diffusioneToString()));
    numeroArticoliEdit->setText(QString::number(periodico->getNumeroArticoli()));
    dataEdit->setDate(QDate::fromString(QString::fromStdString(periodico->getData()), "dd/MM/yyyy"));
}

void PeriodicoEditWidget::clearPeriodicoFields() {
    if (periodoBox)
        periodoBox->setCurrentIndex(-1);
    if (diffusioneBox)
        diffusioneBox->setCurrentIndex(-1);
    if (numeroArticoliEdit)
        numeroArticoliEdit->clear();
    if (dataEdit)
        dataEdit->clear();
}
