#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QThread>

#include "src/gui/MainWindow.h"
#include "model/persistence/JsonManager.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString appDir = QApplication::applicationDirPath();
    QString dataDir = appDir + "/data";
    QString jsonPath = dataDir + "/biblioteca.json";

    // Crea la directory se non esiste
    QDir dir;
    if (!dir.exists(dataDir)) {
        dir.mkpath(dataDir);
        qDebug() << "Creata directory:" << dataDir;
    }

    qDebug() << "Percorso file JSON:" << jsonPath;

    JsonManager jsonManager(jsonPath);
    QList<Biblioteca*> initialData = jsonManager.loadBibliotecaListFromJson();

    // Configurazione globale dell'applicazione
    app.setApplicationName("MyStackedApp");

    // Creazione e visualizzazione della finestra principale
    MainWindow mainWindow(&jsonManager);
    mainWindow.show();

    return app.exec();
}
