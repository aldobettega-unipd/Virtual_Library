#ifndef MEDIACATEGORYSECTION_H
#define MEDIACATEGORYSECTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>

#include "../model/media/biblioteca.h"
#include "MediaBox.h"

class MediaCategorySection : public QWidget
{
    Q_OBJECT
public:
    explicit MediaCategorySection(const QString& nome, const QString& icona, QWidget* parent = nullptr);

    void setMediaData(const QList<Biblioteca*>& mediaList);
    void clearMedia();

    void applyFilters(const QString& searchText, const QMap<QString, QVariant>& filters);

    void setNomeCategoria(const QString& nome);
    void setIconaCategoria(const QString& icona);
private:
    QString nomeCategoria;
    QString iconaCategoria;
    QList<Biblioteca*> allMediaData;
    QList<Biblioteca*> filteredMediaData;
    QList<MediaBox*> mediaBoxes;

    QVBoxLayout* mainLayout;
    QLabel* headerLabel;
    QScrollArea* areaOrizzontale;
    QWidget* scrollContent;
    QHBoxLayout* mediaLayout;

    void setupUI();
    void updateHeader();
    void refreshMediaDisplay();
    void clearMediaBoxes();
    void createMediaBoxes();
    bool matchesFilters(Biblioteca* media, const QString& searchText, const QMap<QString, QVariant>& filters) const;

signals:
    void mediaClicked(Biblioteca* media);

private slots:
    void onMediaBoxClicked(Biblioteca* media);

};

#endif // MEDIACATEGORYSECTION_H
