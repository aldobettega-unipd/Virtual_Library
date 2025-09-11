// BaseEditWidget.h
#ifndef BASEEDITWIDGET_H
#define BASEEDITWIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QEnterEvent>

#include "../model/media/biblioteca.h"
#include "../model/media/multimedia.h"
#include "../model/media/media_cartaceo.h"

class BaseEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BaseEditWidget(QWidget* parent = nullptr);
    virtual ~BaseEditWidget() = default;

    // Metodi pubblici per interagire con il widget
    virtual void setMedia(Biblioteca* media) = 0;
    virtual Biblioteca* createMedia() = 0;
    virtual void updateMedia() = 0;
    virtual void clearFields() = 0;
    virtual bool validateFields() = 0;

protected:
    // Campi Biblioteca
    QLineEdit* titoloEdit;
    QLineEdit* annoPubblicazioneEdit;
    QLineEdit* idEdit;
    QLineEdit* genereEdit;
    QLabel* immagineLabel;
    QPushButton* browseButton;
    QLineEdit* linguaEdit;
    QSpinBox* copieSpin;

    // campi multimedia
    QLineEdit* supportoTecnoEdit;
    QLineEdit* casaDiProdEdit;
    QLineEdit* durataEdit;

    // Campi Media cartaceo
    QLineEdit* numeroPagineEdit;
    QLineEdit* editoreEdit;

    QString imagePath;
    QVBoxLayout* mainLayout;

    // Crezione sezioni
    void createBibliotecaSection();
    void createMultimediaSection();
    void createMediaCartaceoSection();

    // Validazione input
    bool validateBibliotecaFields();
    bool validateMultimediaFields();
    bool validateMediaCartaceoFields();

    // Popolazione form
    void populateBibliotecaFields(Biblioteca* media);
    void populateMultimediaFields(Multimedia* media);
    void populateMediaCartaceoFields(Media_cartaceo* media);

    // Pulizia form
    void clearBibliotecaFields();
    void clearMultimediaFields();
    void clearMediaCartaceoFields();

    void enterEvent(QEnterEvent* event) override;


public slots:
    void onBrowseImage();
};

#endif // BASEEDITWIDGET_H
