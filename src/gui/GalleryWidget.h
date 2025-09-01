#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QList>

#include "../model/media/biblioteca.h"
#include "../model/observers/JsonObserver.h"

class GalleryWidget : public QScrollArea
{
    Q_OBJECT
private:
    bool adminMode;
    QWidget* containerWidget;
    QGridLayout* gridLayout;
    QList<Biblioteca*> allMediaData;
    QList<Biblioteca*> filteredMediaData;

    bool matchesFilters(Biblioteca* media, const QString& text, const QMap<QString, QVariant>& filters) const;

public:
    explicit GalleryWidget(bool isAdmin = false, QWidget* parent = nullptr);
    void setMediaData(const QList<Biblioteca*>& data);
    void filterByText(const QString& text);
    void applyFilters(const QMap<QString, QVariant>& filters);
    void refreshGallery();

signals:
    void editMediaRequested(Biblioteca* media);
    void deleteMediaRequested(Biblioteca* media);
    void mediaClicked(Biblioteca* media);

};

#endif // GALLERYWIDGET_H
