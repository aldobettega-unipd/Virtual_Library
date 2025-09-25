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
    ~MainWindow();

private:
    void setupConnections();
    void loadInitialData();

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

    void gestisciPrenota(Biblioteca* media);
    void gestisciRestituisci(Biblioteca* media);
};

#endif // MAINWINDOW_H
