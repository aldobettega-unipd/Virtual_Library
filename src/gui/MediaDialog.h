#ifndef MEDIADIALOG_H
#define MEDIADIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QStackedWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include "../model/media/biblioteca.h"


class MediaDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* titoloEdit;
    QLineEdit* annoPubblicazioneEdit;
    QLineEdit* idEdit;
    QLineEdit* genereEdit;
    QLabel* immagineLabel;
    QPushButton* browseButton;
    QLineEdit* linguaEdit;
    QSpinBox* copieSpin;
    QLineEdit* copieInPrestitoEdit;
    QLineEdit* disponibileEdit;
    QLineEdit* numeroPagineEdit;
    QLineEdit* editoreEdit;
    QLineEdit* lettoEdit;
    QLineEdit* autoreEdit;

    QString imagePath;

    QComboBox* typeCombo;
    QStackedWidget* formStack;

    QWidget* libroForm;

    void setupUI();

    void setupBibliotecaForm(QWidget* form);
    void setupMediaCartaceoForm(QWidget* form);
    void setupLibroForm();
private slots:
    void onMediaTypeChanged(int index);
    void clearFields();
    void onBrowseImage();
public:
    explicit MediaDialog(QWidget* parent = nullptr);
    Biblioteca* createMedia() const;
};

#endif // MEDIADIALOG_H
