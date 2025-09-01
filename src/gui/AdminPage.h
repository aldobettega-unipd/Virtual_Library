#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include "BasePage.h"

class AdminPage : public BasePage
{
    Q_OBJECT
public:
    explicit AdminPage(QWidget* parent = nullptr);

protected:
    void setupSpecificUI() override;
    void setupSpecificConnections() override;

private:
    QPushButton* addButton;

signals:
    void onEditMedia(Biblioteca* media);
    void onDeleteMedia(Biblioteca* media);
    void createNewObject(Biblioteca* newMedia);
    void removeObject(Biblioteca* newMedia);
    void modifyObject(Biblioteca* newMedia);

private slots:
    void onAddButtonClicked();
    void handleEditMedia(Biblioteca* media);
    void handleDeleteMedia(Biblioteca* media);

};

#endif // ADMINPAGE_H
