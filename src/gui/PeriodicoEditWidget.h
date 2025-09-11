#ifndef PERIODICOEDITWIDGET_H
#define PERIODICOEDITWIDGET_H

#include "BaseEditWidget.h"
#include "../model/media/periodico.h"

#include <QWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>

class PeriodicoEditWidget : public BaseEditWidget
{
public:
    explicit PeriodicoEditWidget(QWidget* parent = nullptr);

    void setMedia(Biblioteca* media) override;
    Biblioteca* createMedia() override;
    void updateMedia() override;
    void clearFields() override;
    bool validateFields() override;

private:
    QComboBox* periodoBox;
    QComboBox* diffusioneBox;
    QLineEdit* numeroArticoliEdit;
    QDateEdit* dataEdit;

    Periodico* currentPeriodico;

    void setupUI();

    void populatePeriodicoFields(Periodico* periodico);
    void clearPeriodicoFields();

};

#endif // PERIODICOEDITWIDGET_H
