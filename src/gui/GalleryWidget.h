#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>
#include <QMap>
#include <QVariant>

#include "../model/media/biblioteca.h"
#include "../model/observers/JsonObserver.h"

class MediaCategorySection;

class GalleryWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit GalleryWidget(bool isAdmin = false, QWidget* parent = nullptr);
    void setMediaData(const QList<Biblioteca*>& data);
    void filterByText(const QString& text);
    void applyFilters(const QMap<QString, QVariant>& filters);
    void refreshGallery();

private:
    bool adminMode;
    QWidget* containerWidget;
    QVBoxLayout* mainLayout;

    QMap<QString, MediaCategorySection*> categorySections;

    QList<Biblioteca*> allMediaData;
    QString currentSearchText;
    QMap<QString, QVariant> currentFilters;

    struct CategoryConfig {
        QString displayName;
        QString icon;
        int order;
    };

    static QMap<QString, CategoryConfig> getCategoryConfigs();

    void setupUI();
    void initializeSections();
    void redistributeMediaByCategory();
    void updateAllSections();
    QString getMediaCategory(Biblioteca* media) const;
    void connectSectionSignals();

signals:
    void editMediaRequested(Biblioteca* media);
    void deleteMediaRequested(Biblioteca* media);
    void mediaClicked(Biblioteca* media);

private slots:
    void onMediaClicked(Biblioteca* media);

};

#endif // GALLERYWIDGET_H
