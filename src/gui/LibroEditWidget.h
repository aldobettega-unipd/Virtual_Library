#ifndef LIBROEDITWIDGET_H
#define LIBROEDITWIDGET_H

#include "BaseEditWidget.h"
#include "../model/media/libro.h"

class LibroEditWidget : public BaseEditWidget
{
    Q_OBJECT

public:
    explicit LibroEditWidget(QWidget* parent = nullptr);

    // Implementazione metodi virtuali
    void setMedia(Biblioteca* media) override;
    Biblioteca* createMedia() override;
    void updateMedia() override;
    void clearFields() override;
    bool validateFields() override;

private:
    QLineEdit* autoreEdit;

    Libro* currentLibro;

    void setupUI();

    // Metodi specifici
    void populateLibroFields(Libro* libro);
    void clearLibroFields();
    bool validateLibroFields();
};

#endif // LIBROEDITWIDGET_H
