#include "GalleryWidget.h"
#include "MediaCategorySection.h"
#include "../model/media/libro.h"
#include "../model/media/periodico.h"
#include "../model/media/media_video.h"
#include "../model/media/cd.h"

#include <QDebug>

GalleryWidget::GalleryWidget(bool isAdmin, QWidget* parent)
    : QScrollArea(parent), adminMode(isAdmin)
{
    setupUI();
    initializeSections();
}

void GalleryWidget::setupUI() {
    containerWidget = new QWidget(this);
    containerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QVBoxLayout(containerWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 20);

    // Configurazione scroll area principale (verticale)
    setWidget(containerWidget);
    setWidgetResizable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setMinimumWidth(800);
    setMinimumHeight(600);
}

void GalleryWidget::initializeSections() {
    auto categoryConfigs = getCategoryConfigs();

    QList<QPair<int, QString>> orderedCategories;
    for (auto it = categoryConfigs.begin(); it != categoryConfigs.end(); ++it) {
        orderedCategories.append({it.value().order, it.key()});
    }

    std::sort(orderedCategories.begin(), orderedCategories.end());

    for (const auto& pair : orderedCategories) {
        const QString& categoryKey = pair.second;
        const CategoryConfig& config = categoryConfigs[categoryKey];

        MediaCategorySection* section = new MediaCategorySection(
            config.displayName,
            config.icon,
            containerWidget
            );

        categorySections[categoryKey] = section;
        mainLayout->addWidget(section);

        qDebug() << "Created section for:" << categoryKey << "(" << config.displayName << ")";
    }

    // Spazio finale per layout
    mainLayout->addStretch();

    connectSectionSignals();
}

void GalleryWidget::connectSectionSignals() {
    // Connetti tutti i segnali delle sezioni
    for (auto* section : categorySections.values()) {
        connect(section, &MediaCategorySection::mediaClicked,
                this, &GalleryWidget::onMediaClicked);
    }
}

QMap<QString, GalleryWidget::CategoryConfig> GalleryWidget::getCategoryConfigs() {
    static QMap<QString, CategoryConfig> configs = {
        {"Libro", {"Libri", "📚", 1}},
        {"Periodico", {"Periodici", "📰", 2}},
        {"Media_video", {"Video", "🎬", 3}},
        {"Cd", {"Audio", "🎵", 4}}
    };
    return configs;
}

void GalleryWidget::setMediaData(const QList<Biblioteca*>& data) {
    qDebug() << "GalleryWidget: Setting media data, count:" << data.size();

    allMediaData = data;
    redistributeMediaByCategory();
}

void GalleryWidget::redistributeMediaByCategory() {
    // Raggruppa i media per categoria
    QMap<QString, QList<Biblioteca*>> mediaByCategory;

    for (Biblioteca* media : allMediaData) {
        QString category = getMediaCategory(media);
        mediaByCategory[category].append(media);

        qDebug() << "Media:" << QString::fromStdString(media->getTitolo())
                 << "-> Category:" << category;
    }

    // Assegna i dati alle sezioni appropriate
    for (auto it = mediaByCategory.begin(); it != mediaByCategory.end(); ++it) {
        const QString& category = it.key();
        const QList<Biblioteca*>& mediaList = it.value();

        if (categorySections.contains(category)) {
            categorySections[category]->setMediaData(mediaList);
            qDebug() << "Assigned" << mediaList.size() << "items to" << category << "section";
        } else {
            qWarning() << "No section found for category:" << category;
        }
    }

    // Assicurati che le sezioni senza media siano vuote
    for (auto* section : categorySections.values()) {
        QString sectionCategory;
        // Trova la categoria di questa sezione
        for (auto it = categorySections.begin(); it != categorySections.end(); ++it) {
            if (it.value() == section) {
                sectionCategory = it.key();
                break;
            }
        }

        if (!mediaByCategory.contains(sectionCategory)) {
            section->clearMedia();
        }
    }

    updateAllSections();
}

QString GalleryWidget::getMediaCategory(Biblioteca* media) const {
    // Determina la categoria basandosi sul tipo di oggetto
    if (dynamic_cast<Libro*>(media)) {
        return "Libro";
    } else if (dynamic_cast<Periodico*>(media)) {
        return "Periodico";
    } else if (dynamic_cast<Media_video*>(media)) {
        return "Media_video";
    } else if (dynamic_cast<Cd*>(media)) {
        return "Cd";
    }

    qWarning() << "Unknown media type for:" << QString::fromStdString(media->getTitolo());
    return "Unknown";
}

void GalleryWidget::filterByText(const QString& text) {
    currentSearchText = text;
    updateAllSections();
}

void GalleryWidget::applyFilters(const QMap<QString, QVariant>& filters) {
    currentFilters = filters;

    // Estrai il testo di ricerca se presente nei filtri
    if (filters.contains("searchText")) {
        currentSearchText = filters.value("searchText").toString();
    }

    updateAllSections();
}

void GalleryWidget::updateAllSections() {
    qDebug() << "GalleryWidget: Updating all sections with search:" << currentSearchText;

    // Applica filtri a tutte le sezioni
    for (auto* section : categorySections.values()) {
        section->applyFilters(currentSearchText, currentFilters);
    }
}

void GalleryWidget::refreshGallery() {
    // Manteniamo questo metodo per compatibilità
    redistributeMediaByCategory();
}

void GalleryWidget::onMediaClicked(Biblioteca* media) {
    qDebug() << "GalleryWidget: Media clicked:" << QString::fromStdString(media->getTitolo());
    emit mediaClicked(media);
}
