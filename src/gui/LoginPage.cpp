#include "LoginPage.h"
#include <QDebug>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {

    areaUtente = new QPushButton("Area Utente", this);
    areaAdmin = new QPushButton("Area Admin", this);

    layout = new QVBoxLayout(this);
    layout->addWidget(areaUtente);
    layout->addWidget(areaAdmin);

    connect(areaUtente, &QPushButton::clicked, this, [this]() {
        qDebug() << "Richiesta area utente";
        emit requestShowUserArea();
    });
    connect(areaAdmin, &QPushButton::clicked, this, [this]() {
        qDebug() << "Richiesta area admin";
        emit requestShowAdminArea();
    });


    setupStyles();
}

void LoginPage::setupStyles() {
    areaUtente->setFixedSize(200, 40);
    areaAdmin->setFixedSize(200, 40);

    QString buttonStyle =
        "QPushButton {"
        "   background-color: white;"
        "   border: 2px solid black;"
        "   color: black;"
        "   padding: 5px;"
        "   border-radius: 3px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e0e0e0;"  // Grigio chiaro invece di nero
        "   color: black;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #a0a0a0;"  // Grigio medio
        "}";

    areaUtente->setStyleSheet(buttonStyle);
    areaAdmin->setStyleSheet(buttonStyle);
    layout->setAlignment(Qt::AlignCenter);
}





