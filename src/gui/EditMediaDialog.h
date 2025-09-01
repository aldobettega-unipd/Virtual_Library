#ifndef EDITMEDIADIALOG_H
#define EDITMEDIADIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QStackedWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include "../model/media/biblioteca.h"

class EditMediaDialog : public QDialog
{
    Q_OBJECT

private:
    Biblioteca* mediaToEdit;

    // UI components
    QLineEdit* titoloEdit;
    QLineEdit* annoPubblicazioneEdit;
    QLineEdit* idEdit;
    QLineEdit* genereEdit;
    QLabel* immagineLabel;
    QPushButton* browseButton;
    QLineEdit* linguaEdit;
    QSpinBox* copieSpin;
    QLineEdit* numeroPagineEdit;
    QLineEdit* editoreEdit;
    QLineEdit* autoreEdit;

    QString imagePath;

    QComboBox* typeCombo;
    QStackedWidget* formStack;
    QWidget* libroForm;

    // Setup methods
    void setupUI();
    void setupBibliotecaForm(QWidget* form);
    void setupMediaCartaceoForm(QWidget* form);
    void setupLibroForm();
    void populateFields();
    bool validateFields() const;

private slots:
    void onBrowseImage();
    void onResetClicked();

public:
    explicit EditMediaDialog(Biblioteca* media, QWidget* parent = nullptr);
    void updateMedia();
};

#endif // EDITMEDIADIALOG_H
