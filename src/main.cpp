#include <QApplication>
#include <QDir>
#include <QDebug>
#include "gui/MainWindow.h"
#include "model/persistence/JsonManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Percorso semplificato - JSON sempre nella cartella data della root del progetto
    QString jsonPath = "./data/biblioteca.json";

    JsonManager jsonManager(jsonPath);
    QList<Biblioteca*> initialData = jsonManager.loadBibliotecaListFromJson();

    app.setApplicationName("Biblioteca");
    MainWindow mainWindow(&jsonManager);
    mainWindow.show();

    return app.exec();
}
