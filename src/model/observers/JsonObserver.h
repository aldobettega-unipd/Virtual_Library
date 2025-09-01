#ifndef JSONOBSERVER_H
#define JSONOBSERVER_H

#include <QList>

class Biblioteca;

//Questa classe osserva i cambiamenti nei darti gestititi dal JsonManager: gli oggetti JsonObserver* sono contenuti in
//una lista gestita da JsonManager.

class JsonObserver
{
public:
    virtual ~JsonObserver() = default;
    virtual void onBibliotecaUpdated(const QList<Biblioteca*>& newBiblioteca) = 0;
};

#endif // JSONOBSERVER_H
