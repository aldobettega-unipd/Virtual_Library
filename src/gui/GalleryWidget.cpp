#include "GalleryWidget.h"
#include "MediaBox.h"
#include "../model/media/media_cartaceo.h"
#include "../model/media/libro.h"

#include <QMap>
#include <QVariant>
#include <QLayoutItem>
#include <QDebug>



GalleryWidget::GalleryWidget(bool isAdmin, QWidget* parent) : QScrollArea(parent), adminMode(isAdmin) {
    containerWidget = new QWidget(this);
    gridLayout = new QGridLayout(containerWidget);
    gridLayout->setSpacing(10);
    gridLayout->setContentsMargins(10, 10, 10, 10);

    setWidget(containerWidget);
    setWidgetResizable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void GalleryWidget::setMediaData(const QList<Biblioteca*>& data) {
    allMediaData = data;
    filteredMediaData = data;
    refreshGallery();
}

void GalleryWidget::filterByText(const QString& text) {
    filteredMediaData.clear();

    for (auto* media : allMediaData) {
        QString searchStr = text.toLower();
        QString titolo = QString::fromStdString(media->getTitolo()).toLower();
        QString genere = QString::fromStdString(media->getGenere());

        if (titolo.contains(searchStr) || genere.contains(searchStr)) {
            filteredMediaData.append(media);
        }
    }
    refreshGallery();
}

void GalleryWidget::applyFilters(const QMap<QString, QVariant>& filters) {
    filteredMediaData.clear();

    for (auto* media : allMediaData) {
        if (matchesFilters(media, "", filters)) {
            filteredMediaData.append(media);
        }
    }

    refreshGallery();
}

void GalleryWidget::refreshGallery() {
    qDebug() << "Refreshing gallery, admin mode:" << adminMode << ", items:" << filteredMediaData.size();

    // Clean existing layout
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    // Add new elements
    int row = 0, col = 0;
    const int columns = 4;

    for (auto* media : filteredMediaData) {
        // NULL CHECK - crucial!
        if (!media) {
            qWarning() << "Null media pointer in filteredMediaData!";
            continue;
        }

        MediaBox* mediaBox = nullptr;
        try {
            mediaBox = new MediaBox(media, containerWidget);
            connect(mediaBox, &MediaBox::clicked, this, &GalleryWidget::mediaClicked);

            if (mediaBox)
                gridLayout->addWidget(mediaBox, row, col);

        } catch (const std::exception& e) {
            qCritical() << "Error creating MediaBox:" << e.what();
            continue;
        }

        col++;
        if (col >= columns) {
            col = 0;
            row++;
        }
    }
}

bool GalleryWidget::matchesFilters(Biblioteca* media, const QString& text,
                                   const QMap<QString, QVariant>& filters) const {
    //filtro per il testo
    if (!text.isEmpty()) {
        QString searchStr = text.toLower();
        QString titolo = QString::fromStdString(media->getTitolo()).toLower();
        QString genere = QString::fromStdString(media->getGenere()).toLower();

        if (!titolo.contains(searchStr) && !genere.contains(searchStr))
            return false;
    }

    for (auto it = filters.begin(); it != filters.end(); ++it) {
        const QString& key = it.key();
        const QVariant& value = it.value();

        if (key == "anno") {
            QString annoPubblicazione = QString::fromStdString(media->getAnnoPubblicazione());
            bool ok;
            int anno = annoPubblicazione.toInt(&ok);

            if(ok) {
                QString range = value.toString();
                if (range == "2000-oggi" && anno < 2000) return false;
                else if (range == "1900-1999" && (anno < 1900 || anno > 1999)) return false;
                else if (range == "1800-1899" && (anno < 1800 || anno > 1899)) return false;
                else if (range == "1700-1799" && (anno < 1700 || anno > 1799)) return false;
                else if (range == "prima-1700" && anno >= 1700) return false;

            }
        } else if (key == "autore") {
            if (auto libro = dynamic_cast<Libro*>(media)) {
                if (!QString::fromStdString(libro->getAutore()).contains(value.toString(), Qt::CaseInsensitive))
                    return false;
            }
        } else if (key == "genere") {
            if (!QString::fromStdString(media->getGenere()).contains(value.toString(), Qt::CaseInsensitive))
                return false;
        } else if (key == "disponibile") {
            if (!media->getDisponibilità()) return false;
        }



        if (key == "solo_non_letti" && value.toBool()) {
            if (auto cartaceo = dynamic_cast<Media_cartaceo*>(media)) {
                if (cartaceo->getLetto()) return false;
            }
        }
        else if (key == "solo_disponibili" && value.toBool()) {
            if (!media->getDisponibilità()) return false;
        }
        else if (key == "genere" && value.toString() != "Tutti") {
            QString genereMedia = QString::fromStdString(media->getGenere());
            if (genereMedia != value.toString()) return false;
        }
    }

    return true;
}








