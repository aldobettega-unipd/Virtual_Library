#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "LoginPage.h"
#include "UserPage.h"
#include "AdminPage.h"
#include "UserDetailPage.h"
#include "AdminDetailPage.h"
#include "MediaEditManager.h"
#include "../model/persistence/JsonManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(JsonManager* jsonManager, QWidget *parent = nullptr);

private:
    void setupConnections();
    void loadInitialData();
    void reconnectJsonManagerSignals();

    QStackedWidget *stack;
    LoginPage *loginPage;
    UserPage *userPage;
    AdminPage *adminPage;
    UserDetailPage *userDetailPage;
    AdminDetailPage *adminDetailPage;
    MediaEditManager* mediaEditManager;
    JsonManager *jsonManager;

private slots:
    void showUserPage();
    void showAdminPage();
    void showLoginPage();
    void showUserDetailPage(Biblioteca* media);
    void showAdminDetailPage(Biblioteca* media);
    void showCreateMediaPage();
    void showEditMediaPage(Biblioteca* media);

    void handlePrenota(Biblioteca* media);
    void handleRestituisci(Biblioteca* media);
    void handleSaveData(const QString& fileName);
    void handleLoadData(const QString& fileName);
};

#endif // MAINWINDOW_H
