#ifndef CDEDITWIDGET_H
#define CDEDITWIDGET_H

#include "BaseEditWidget.h"
#include "../model/media/cd.h"

class CdEditWidget : public BaseEditWidget
{
    Q_OBJECT
public:
    explicit CdEditWidget(QWidget* parent = nullptr);

    void setMedia(Biblioteca* media) override;
    Biblioteca* createMedia() override;
    void updateMedia() override;
    void clearFields() override;
    bool validateFields() override;

private:
    QLineEdit* artistaEdit;
    QLineEdit* nTracceEdit;

    Cd* currentCd;

    void setupUI();
    void populateCdFields(Cd* cd);
    void clearCdFields();
    bool validateCdFields();
};

#endif // CDEDITWIDGET_H
