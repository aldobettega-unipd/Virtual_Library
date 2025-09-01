#include "MainWindow.h"
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(JsonManager* jsonManager, QWidget *parent) : QMainWindow(parent), jsonManager(jsonManager)
{
    if (!jsonManager) {
        QMessageBox::critical(this, "Error", "JsonManager initialization failed");
        QTimer::singleShot(0, this, &QWidget::close);
        return;
    }

    // Inizializza le pagine
    loginPage = new LoginPage(this);
    userPage = new UserPage(this);
    adminPage = new AdminPage(this);
    userDetailPage = new UserDetailPage(this);
    adminDetailPage = new AdminDetailPage(this);

    //OBSERVER PATTERN - JsonManager notifica le pagine
    jsonManager->addObserver(adminPage);
    jsonManager->addObserver(userPage);

    // Crea lo stack
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // Aggiungi le pagine
    stack->addWidget(loginPage); // index 0
    stack->addWidget(userPage);  // index 1
    stack->addWidget(adminPage); // index 2
    stack->addWidget(userDetailPage); // index 3
    stack->addWidget(adminDetailPage); // index 4

    stack->setCurrentWidget(loginPage);

    setupConnections();
    loadInitialData();

    setWindowTitle("Sistema Biblioteca - Demo");
    resize(800, 600);
}

void MainWindow::setupConnections() {
    // Connessioni login
    connect(loginPage, &LoginPage::requestShowUserArea, this, &MainWindow::showUserPage);
    connect(loginPage, &LoginPage::requestShowAdminArea, this, &MainWindow::showAdminPage);

    // Connessioni logout
    connect(userPage, &UserPage::logoutRequested, this, &MainWindow::showLoginPage);
    connect(adminPage, &AdminPage::logoutRequested, this, &MainWindow::showLoginPage);

    //operazioni CRUD di AdminPage
    connect(adminPage, &AdminPage::createNewObject, jsonManager, &JsonManager::saveNewObject);
    connect(adminPage, &AdminPage::removeObject, jsonManager, &JsonManager::deleteObject);
    connect(adminPage, &AdminPage::modifyObject, jsonManager, &JsonManager::updateObject);

    connect(userPage, &UserPage::mediaClicked, this, &MainWindow::showUserDetailPage);
    connect(adminPage, &AdminPage::mediaClicked, this, &MainWindow::showAdminDetailPage);

    connect(userDetailPage, &UserDetailPage::backRequested, this, &MainWindow::showUserPage);
    connect(adminDetailPage, &AdminDetailPage::backRequested, this, &MainWindow::showAdminPage);

    connect(adminDetailPage, &AdminDetailPage::deleteRequested, jsonManager, &JsonManager::deleteObject);
    connect(adminDetailPage, &AdminDetailPage::editRequested, jsonManager, &JsonManager::updateObject);
}

void MainWindow::showUserPage()
{
    loadInitialData();
    stack->setCurrentWidget(userPage);
}

void MainWindow::showAdminPage()
{
    loadInitialData();
    stack->setCurrentWidget(adminPage);
}

void MainWindow::showLoginPage()
{
    stack->setCurrentWidget(loginPage);
}

void MainWindow::showUserDetailPage(Biblioteca* media)
{
    userDetailPage->setMediaData(media);
    stack->setCurrentWidget(userDetailPage);
}

void MainWindow::showAdminDetailPage(Biblioteca* media)
{
    adminDetailPage->setMediaData(media);
    stack->setCurrentWidget(adminDetailPage);
}



void MainWindow::loadInitialData()
{
    qDebug() << "Starting loadInitialData";
    try {
        QList<Biblioteca*> initialData = jsonManager->loadBibliotecaListFromJson();

        if (initialData.isEmpty()) {
            qWarning() << "Nessun dato caricato o file vuoto";
        } else {
            qDebug() << "Caricati" << initialData.size() << "elementi";
        }

        // Passa i dati alle pagine
        userPage->onBibliotecaUpdated(initialData);
        adminPage->onBibliotecaUpdated(initialData);



    } catch (const std::exception& e) {
        qCritical() << "Error loading data:" << e.what();
        QMessageBox::warning(this, "Error", QString("Failed to load data: %1").arg(e.what()));
    }
}
