#ifndef BASEPAGE_H
#define BASEPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "SearchWidget.h"
#include "GalleryWidget.h"

class BasePage : public QWidget, public JsonObserver
{
    Q_OBJECT;
public:
    BasePage(QWidget* parent = nullptr);
    void onBibliotecaUpdated(const QList<Biblioteca*>& data) override;

signals:
    void logoutRequested();
    void mediaClicked(Biblioteca* media);

protected:
    QVBoxLayout *mainLayout;
    QWidget* menuBar;
    SearchWidget *searchWidget;
    GalleryWidget* galleryWidget;
    QPushButton* logoutButton;

    QList<Biblioteca*> currentData;

    //metodi template
    virtual void setupSpecificUI() = 0;
    virtual void setupSpecificConnections() = 0;

    //metodi condivisi
    void setupCommonUI();
    void setupCommonConnections();


private:
    void setupMenuBar();
};

#endif // BASEPAGE_H
