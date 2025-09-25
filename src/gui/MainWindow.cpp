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
    mediaEditManager = new MediaEditManager(this);

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
    stack->addWidget(mediaEditManager); // index 5

    stack->setCurrentWidget(loginPage);

    setupConnections();
    loadInitialData();

    setStyleSheet("QWidget { background-color: white; color: black; }");

    setWindowTitle("Sistema Biblioteca - Demo");
    resize(1200, 1000);
}

MainWindow::~MainWindow() {
    if (jsonManager) {
        delete jsonManager;
    }
}

void MainWindow::setupConnections() {
    // Connessioni login
    connect(loginPage, &LoginPage::requestShowUserArea, this, &MainWindow::showUserPage);
    connect(loginPage, &LoginPage::requestShowAdminArea, this, &MainWindow::showAdminPage);

    // Connessioni logout
    connect(userPage, &BasePage::logoutRequested, this, &MainWindow::showLoginPage);
    connect(adminPage, &BasePage::logoutRequested, this, &MainWindow::showLoginPage);

    // Apertura di DetailPage
    connect(userPage, &BasePage::mediaClicked, this, &MainWindow::showUserDetailPage);
    connect(adminPage, &BasePage::mediaClicked, this, &MainWindow::showAdminDetailPage);

    // Uscita dalla detailPage
    connect(userDetailPage, &BaseDetailPage::backRequested, this, &MainWindow::showUserPage);
    connect(adminDetailPage, &BaseDetailPage::backRequested, this, &MainWindow::showAdminPage);

    // Operazioni di PRENOTA e RESTITUISCI
    connect(adminDetailPage, &BaseDetailPage::prenotaRequested, this, &MainWindow::gestisciPrenota);
    connect(userDetailPage, &BaseDetailPage::prenotaRequested, this, &MainWindow::gestisciPrenota);

    connect(adminDetailPage, &BaseDetailPage::restituisciRequested, this, &MainWindow::gestisciRestituisci);
    connect(userDetailPage, &BaseDetailPage::restituisciRequested, this, &MainWindow::gestisciRestituisci);

    // Operazione manuale di salvataggio biblioteca
    connect(adminPage, &AdminPage::saveDataRequested, jsonManager, &JsonManager::saveToFile);
    // Operazione manuale di caricamento biblioteca
    connect(adminPage, &AdminPage::loadDataRequested, jsonManager, &JsonManager::loadFromFile);
    // Apertura CreatePage dopo pressione di AGGIUNGI
    connect(adminPage, &AdminPage::createNewObject, this, &MainWindow::showCreateMediaPage);
    // Apertura EditPage dopo pressione di EDIT
    connect(adminDetailPage, &AdminDetailPage::editRequested, this, &MainWindow::showEditMediaPage);

    // Operazione di DELETE
    connect(adminDetailPage, &AdminDetailPage::deleteRequested, jsonManager, &JsonManager::deleteObject);

    // Operazione di SAVE
    connect(mediaEditManager, &MediaEditManager::mediaCreated, jsonManager, &JsonManager::saveNewObject);
    connect(mediaEditManager, &MediaEditManager::mediaCreated, this, &MainWindow::showAdminPage);
    // Operazione di UPDATE
    connect(mediaEditManager, &MediaEditManager::mediaUpdated, jsonManager, &JsonManager::updateObject);
    connect(mediaEditManager, &MediaEditManager::mediaUpdated, this, &MainWindow::showAdminPage);
    // Operazione di ANNULLA
    connect(mediaEditManager, &MediaEditManager::operationCancelled, this, &MainWindow::showAdminPage);
    // Operazione di BACK
    connect(mediaEditManager, &MediaEditManager::backRequested, this, &MainWindow::showAdminPage);
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

void MainWindow::gestisciPrenota(Biblioteca* media) {
    try {
        if (media->getCopieInPrestito() < media->getCopieTotali()) {
            jsonManager->savePrenota(media);
        } else {
            QMessageBox::warning(this, "Error", "Il media non è disponibile");
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }

    if (stack->currentWidget() == userDetailPage) {
        userDetailPage->refreshDisplay();
    } else if (stack->currentWidget() == adminDetailPage) {
        adminDetailPage->refreshDisplay();
    }
}

void MainWindow::gestisciRestituisci(Biblioteca* media) {
    try {
        if (media->getCopieInPrestito() > 0) {
            jsonManager->saveRestituisci(media);
        } else {
            QMessageBox::warning(this, "Error", "Al momento non possiedi il media");
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
    if (stack->currentWidget() == userDetailPage) {
        userDetailPage->refreshDisplay();
    } else if (stack->currentWidget() == adminDetailPage) {
        adminDetailPage->refreshDisplay();
    }
}


void MainWindow::loadInitialData()
{
    QList<Biblioteca*> initialData = jsonManager->loadBibliotecaListFromJson();

    userPage->onBibliotecaUpdated(initialData);
    adminPage->onBibliotecaUpdated(initialData);

}

void MainWindow::showCreateMediaPage() {
    mediaEditManager->enterCreateMode();
    stack->setCurrentWidget(mediaEditManager);
}

void MainWindow::showEditMediaPage(Biblioteca* media) {
    if (media) {
        mediaEditManager->enterEditMode(media);
        stack->setCurrentWidget(mediaEditManager);
    }
}


