#ifndef BASEDETAILPAGE_H
#define BASEDETAILPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../model/visitors/VisitorWidget.h"

class BaseDetailPage : public QWidget
{
    Q_OBJECT
public:
    explicit BaseDetailPage(QWidget* parent = nullptr);
    void setMediaData(Biblioteca* media);
    void refreshDisplay();

signals:
    void backRequested();

protected:
    //metodi template
    virtual void setupSpecificUI() = 0;
    virtual void setupSpecificConnections() = 0;

    //metodi condivisi
    void setupCommonUI();
    void setupCommonConnections();
    void clearContent();

    Biblioteca* currentMedia;
    VisitorWidget* visitorWidget;

    QVBoxLayout* mainLayout;
    QVBoxLayout* contentLayout;
    QWidget* headerWidget;
    QHBoxLayout* headerLayout;
    QPushButton* backButton;
    QLabel* titleLabel;
    QWidget* contentArea;

private slots:
    void onBackClicked();

};

#endif // BASEDETAILPAGE_H
