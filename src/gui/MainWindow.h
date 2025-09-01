#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "LoginPage.h"
#include "UserPage.h"
#include "AdminPage.h"
#include "UserDetailPage.h"
#include "AdminDetailPage.h"
#include "../model/persistence/JsonManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(JsonManager* jsonManager, QWidget *parent = nullptr);

private slots:
    void showUserPage();
    void showAdminPage();
    void showLoginPage();
    void showUserDetailPage(Biblioteca* media);
    void showAdminDetailPage(Biblioteca* media);
private:
    void setupConnections();
    void loadInitialData();

    QStackedWidget *stack;
    LoginPage *loginPage;
    UserPage *userPage;
    AdminPage *adminPage;
    UserDetailPage *userDetailPage;
    AdminDetailPage *adminDetailPage;
    QWidget* lastPage;
    JsonManager *jsonManager;

};

#endif // MAINWINDOW_H
