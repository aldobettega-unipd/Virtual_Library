#ifndef ADMINDETAILPAGE_H
#define ADMINDETAILPAGE_H

#include "BaseDetailPage.h"

class AdminDetailPage : public BaseDetailPage
{
    Q_OBJECT
public:
    explicit AdminDetailPage(QWidget* parent = nullptr);

private:
    QPushButton* editButton;
    QPushButton* deleteButton;

protected:
    void setupSpecificUI() override;
    void setupSpecificConnections() override;

signals:
    void editRequested(Biblioteca* media);
    void deleteRequested(Biblioteca* media);

private slots:
    void onEditClicked();
    void onDeleteClicked();
};

#endif // ADMINDETAILPAGE_H
