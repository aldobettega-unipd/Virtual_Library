#include "LibroEditWidget.h"
#include <QDebug>

LibroEditWidget::LibroEditWidget(QWidget* parent)
    : BaseEditWidget(parent), autoreEdit(nullptr), currentLibro(nullptr)
{
    setupUI();
}

void LibroEditWidget::setupUI() {
    createBibliotecaSection();
    createMediaCartaceoSection();

    QWidget* libroSection = new QWidget(this);
    QFormLayout* libroLayout = new QFormLayout(libroSection);

    autoreEdit = new QLineEdit(libroSection);
    libroLayout->addRow("Autore*:", autoreEdit);

    mainLayout->addWidget(libroSection);
    mainLayout->addStretch();
}

void LibroEditWidget::setMedia(Biblioteca* media) {
    currentLibro = dynamic_cast<Libro*>(media);

    if (currentLibro) {
        // il puntatore esiste -> sono in modalità modifica
        populateBibliotecaFields(currentLibro);
        populateMediaCartaceoFields(currentLibro);
        populateLibroFields(currentLibro);
    } else {
        // Modalità creazione - pulisci tutti i campi
        clearFields();
    }
}

Biblioteca* LibroEditWidget::createMedia() {
    if (!validateFields())
        return nullptr;

    try {
        return new Libro(
            titoloEdit->text().toStdString(),
            annoPubblicazioneEdit->text().toStdString(),
            idEdit->text().toStdString(),
            genereEdit->text().toStdString(),
            imagePath.toStdString(),
            linguaEdit->text().toStdString(),
            copieSpin->value(),
            numeroPagineEdit->text().toInt(),
            editoreEdit->text().toStdString(),
            autoreEdit->text().toStdString()
            );
    } catch (const std::exception& e) {
        QMessageBox::critical(const_cast<LibroEditWidget*>(this), "Errore",
                              QString("Errore nella creazione del libro: %1").arg(e.what()));
        return nullptr;
    }
}

void LibroEditWidget::updateMedia() {
    if (!currentLibro || !validateFields())
        return;

    try {
        // Aggiorna tutti i campi del libro
        currentLibro->setTitolo(titoloEdit->text().toStdString());
        currentLibro->setAnnoPubblicazione(annoPubblicazioneEdit->text().toStdString());
        currentLibro->setId(idEdit->text().toStdString());
        currentLibro->setGenere(genereEdit->text().toStdString());
        currentLibro->setImmagine(imagePath.toStdString());
        currentLibro->setLingua(linguaEdit->text().toStdString());
        currentLibro->setCopieTotali(copieSpin->value());
        currentLibro->setNumeroPagine(numeroPagineEdit->text().toInt());
        currentLibro->setEditore(editoreEdit->text().toStdString());
        currentLibro->setAutore(autoreEdit->text().toStdString());

        qDebug() << "Libro aggiornato con successo:" << QString::fromStdString(currentLibro->getTitolo());

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore", QString("Errore nell'aggiornamento del libro: %1").arg(e.what()));
    }
}

void LibroEditWidget::clearFields() {
    clearBibliotecaFields();
    clearMediaCartaceoFields();
    clearLibroFields();
    currentLibro = nullptr;
}

bool LibroEditWidget::validateFields() {
    if (!validateBibliotecaFields() || !validateMediaCartaceoFields() || !validateLibroFields()) {
        return false;
    }
    return true;
}

void LibroEditWidget::populateLibroFields(Libro* libro) {
    autoreEdit->setText(QString::fromStdString(libro->getAutore()));
}

void LibroEditWidget::clearLibroFields() {
    if (autoreEdit)
        autoreEdit->clear();
}

bool LibroEditWidget::validateLibroFields() {
    if (!autoreEdit || autoreEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Il campo Autore è obbligatorio");
        return false;
    }

    return true;
}
