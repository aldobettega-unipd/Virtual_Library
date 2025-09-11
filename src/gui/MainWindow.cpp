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
    connect(adminDetailPage, &BaseDetailPage::prenotaRequested, this, &MainWindow::handlePrenota);
    connect(userDetailPage, &BaseDetailPage::prenotaRequested, this, &MainWindow::handlePrenota);

    connect(adminDetailPage, &BaseDetailPage::restituisciRequested, this, &MainWindow::handleRestituisci);
    connect(userDetailPage, &BaseDetailPage::restituisciRequested, this, &MainWindow::handleRestituisci);

    // Operazione manuale di salvataggio biblioteca
    connect(adminPage, &AdminPage::saveDataRequested, this, &MainWindow::handleSaveData);
    // Operazione manuale di caricamento biblioteca
    connect(adminPage, &AdminPage::loadDataRequested, this, &MainWindow::handleLoadData);
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

void MainWindow::handlePrenota(Biblioteca* media) {
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

void MainWindow::handleRestituisci(Biblioteca* media) {
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

void MainWindow::handleLoadData(const QString& fileName) {
    qDebug() << "MainWindow: Loading and overwriting current file with:" << fileName;

    try {
        // Testa che il file sia valido
        QFile sourceFile(fileName);
        if (!sourceFile.exists()) {
            QMessageBox::warning(this, "Errore", "File non trovato: " + fileName);
            return;
        }

        // Testa il formato JSON
        if (!sourceFile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, "Errore", "Impossibile aprire il file: " + fileName);
            return;
        }

        QByteArray testData = sourceFile.readAll();
        sourceFile.close();

        QJsonDocument testDoc = QJsonDocument::fromJson(testData);
        if (!testDoc.isArray()) {
            QMessageBox::warning(this, "Errore", "Formato JSON non valido");
            return;
        }

        // Se arriviamo qui, il file è valido
        // Ottieni il path del file corrente del JsonManager
        QString currentFilePath = "./data/biblioteca.json"; // O jsonManager->getCurrentFilePath() se hai implementato il metodo

        // Copia il contenuto del file scelto nel file corrente
        QFile currentFile(currentFilePath);
        if (!currentFile.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Errore", "Impossibile scrivere nel file corrente");
            return;
        }

        currentFile.write(testData);
        currentFile.close();

        // Ricarica i dati - JsonManager leggerà automaticamente dal file aggiornato
        QList<Biblioteca*> loadedData = jsonManager->loadBibliotecaListFromJson();

        // Aggiorna le interfacce
        adminPage->onBibliotecaUpdated(loadedData);
        userPage->onBibliotecaUpdated(loadedData);

        QMessageBox::information(this, "Successo",
                                 QString("Caricati %1 elementi da: %2\nFile di lavoro aggiornato.")
                                     .arg(loadedData.size()).arg(fileName));

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore",
                              QString("Errore durante il caricamento: %1").arg(e.what()));
    }
}

void MainWindow::handleSaveData(const QString& fileName) {
    qDebug() << "MainWindow: Saving current data to:" << fileName;

    try {
        // Leggi i dati attuali
        QList<Biblioteca*> currentData = jsonManager->loadBibliotecaListFromJson();

        if (currentData.isEmpty()) {
            QMessageBox::warning(this, "Attenzione", "Nessun dato da salvare.");
            return;
        }

        // Ottieni il contenuto del file corrente
        QString currentFilePath = "./data/biblioteca.json";
        QFile currentFile(currentFilePath);

        if (!currentFile.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, "Errore", "Impossibile leggere il file corrente");
            return;
        }

        QByteArray currentData_bytes = currentFile.readAll();
        currentFile.close();

        // Copia nel file di destinazione
        QFile targetFile(fileName);
        if (!targetFile.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, "Errore", "Impossibile creare il file: " + fileName);
            return;
        }

        targetFile.write(currentData_bytes);
        targetFile.close();

        QMessageBox::information(this, "Successo",
                                 QString("Dati salvati in: %1").arg(fileName));

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Errore",
                              QString("Errore durante il salvataggio: %1").arg(e.what()));
    }
}



