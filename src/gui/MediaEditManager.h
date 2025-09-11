#ifndef MEDIAEDITMANAGER_H
#define MEDIAEDITMANAGER_H

#include <QWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QMessageBox>

#include "MediaVideoEditWidget.h"
#include "PeriodicoEditWidget.h"
#include "LibroEditWidget.h"
#include "CdEditWidget.h"

#include "../model/media/biblioteca.h"

class MediaEditManager : public QWidget
{
    Q_OBJECT

public:
    explicit MediaEditManager(QWidget* parent = nullptr);

    // Metodi per gestire creazione e modifica
    void enterCreateMode();
    void enterEditMode(Biblioteca* media);

private:
    enum Mode {
        CREATE_MODE,
        EDIT_MODE
    };

    Mode currentMode;
    Biblioteca* mediaBeingEdited;
    bool unsavedChanges;

    // UI
    QVBoxLayout* mainLayout;
    QLabel* titleLabel;

    // Sezione selezione tipo (solo per CREATE_MODE)
    QWidget* typeSelectionWidget;
    QComboBox* typeComboBox;

    // Stack dei widget di modifica
    QStackedWidget* editStack;
    MediaVideoEditWidget* videoWidget;
    PeriodicoEditWidget* periodicoWidget;
    LibroEditWidget* libroWidget;
    CdEditWidget* cdWidget;

    // Bottoni
    QWidget* buttonWidget;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* backButton;

    void setupUI();
    void setupConnections();
    void updateUIForMode();
    void setCurrentEditWidget(int index);
    BaseEditWidget* getCurrentEditWidget() const;
    int getMediaTypeIndex(Biblioteca* media) const;
    void updateTitle();
    void resetToCleanState();

    // Metodi helper per gestire i cambiamenti non salvati
    bool confirmDiscardChanges();

signals:
    void mediaCreated(Biblioteca* media);
    void mediaUpdated(Biblioteca* media);
    void operationCancelled();
    void backRequested();

private slots:
    void onMediaTypeChanged(int index);
    void onSaveClicked();
    void onCancelClicked();
    void onBackClicked();
};

#endif // MEDIAEDITMANAGER_H
