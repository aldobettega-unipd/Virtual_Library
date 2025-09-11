#include "MediaCategorySection.h"

MediaCategorySection::MediaCategorySection(const QString& nome, const QString& icona, QWidget* parent)
    : QWidget(parent), nomeCategoria(nome), iconaCategoria(icona),
    mainLayout(nullptr), headerLabel(nullptr), areaOrizzontale(nullptr), scrollContent(nullptr),
    mediaLayout(nullptr)

{
    setupUI();
}

void MediaCategorySection::setupUI() {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 15, 20, 15);

    // Header
    headerLabel = new QLabel(this);
    headerLabel->setFixedHeight(40);
    headerLabel->setStyleSheet("font-size: 30px; font-weight: bold");
    updateHeader();
    mainLayout->addWidget(headerLabel);

    // Scroll area
    areaOrizzontale = new QScrollArea(this);
    areaOrizzontale->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    areaOrizzontale->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    areaOrizzontale->setWidgetResizable(true);
    areaOrizzontale->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    areaOrizzontale->setMinimumWidth(500);
    areaOrizzontale->setMinimumHeight(300);

    // Contenuto scrollabile
    scrollContent = new QWidget();
    scrollContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    mediaLayout = new QHBoxLayout(scrollContent);
    mediaLayout->setSpacing(15); // spazio fra i box
    scrollContent->setLayout(mediaLayout);

    areaOrizzontale->setWidget(scrollContent);

    // Aggiungi al layout principale
    mainLayout->addWidget(areaOrizzontale);

    mainLayout->setStretch(0, 0);
    mainLayout->setStretch(1, 1);
}


void MediaCategorySection::setMediaData(const QList<Biblioteca*>& mediaList) {
    allMediaData = mediaList;
    filteredMediaData = mediaList;
    refreshMediaDisplay();
}

void MediaCategorySection::clearMedia() {
    allMediaData.clear();
    filteredMediaData.clear();
    refreshMediaDisplay();
}

void MediaCategorySection::applyFilters(const QString& searchText, const QMap<QString, QVariant>& filters) {
    filteredMediaData.clear();

    for (auto* media : allMediaData) {
        if (matchesFilters(media, searchText, filters))
            filteredMediaData.append(media);
    }

    refreshMediaDisplay();
}

void MediaCategorySection::updateHeader() {
    if (headerLabel) {
        QString headerText = QString("%1 %2 (%3)").arg(iconaCategoria).arg(nomeCategoria.toUpper()).arg(filteredMediaData.size());
        headerLabel->setText(headerText);
    }
}

void MediaCategorySection::refreshMediaDisplay() {
    clearMediaBoxes();
    updateHeader();

    if (filteredMediaData.isEmpty())
        return;
    else {
        createMediaBoxes();
    }
}

void MediaCategorySection::clearMediaBoxes() {
    for (MediaBox* box : mediaBoxes) {
        mediaLayout->removeWidget(box);
        box->deleteLater();
    }
    mediaBoxes.clear();
}

void MediaCategorySection::createMediaBoxes() {
    for (Biblioteca* media : filteredMediaData) {
        MediaBox* mediaBox = new MediaBox(media, areaOrizzontale);
        mediaBox->setFixedSize(280, 350);
        mediaBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        connect(mediaBox, &MediaBox::clicked, this, &MediaCategorySection::onMediaBoxClicked);

        mediaLayout->addWidget(mediaBox);
        mediaBoxes.append(mediaBox);
    }
}

void MediaCategorySection::onMediaBoxClicked(Biblioteca* media) {
    qDebug() << "Cliccato media box: " << QString::fromStdString(media->getTitolo());
    emit mediaClicked(media);
}

bool MediaCategorySection::matchesFilters(Biblioteca* media, const QString& searchText,
                                          const QMap<QString, QVariant>& filters) const {
    // Copia la stessa logica di filtri da GalleryWidget::matchesFilters()
    if (!searchText.isEmpty()) {
        QString searchStr = searchText.toLower();
        QString titolo = QString::fromStdString(media->getTitolo()).toLower();
        QString id = QString::fromStdString(media->getId()).toLower();

        if (!titolo.contains(searchStr) && !id.contains(searchStr))
            return false;
    }

    for (auto it = filters.begin(); it != filters.end(); ++it) {
        const QString& key = it.key();
        const QVariant& value = it.value();

        if (key == "anni") {
            QStringList anniSelezionati = value.toStringList();
            QString annoPubblicazione = QString::fromStdString(media->getAnnoPubblicazione());
            bool ok;
            int anno = annoPubblicazione.toInt(&ok);

            if (ok && !anniSelezionati.isEmpty()) {
                bool annoTrovato = false;
                for (const QString& range : anniSelezionati) {
                    if (range == "2000-oggi" && anno >= 2000) {
                        annoTrovato = true;
                        break;
                    } else if (range == "1900-1999" && anno >= 1900 && anno <= 1999) {
                        annoTrovato = true;
                        break;
                    } else if (range == "1800-1899" && anno >= 1800 && anno <= 1899) {
                        annoTrovato = true;
                        break;
                    } else if (range == "1700-1799" && anno >= 1700 && anno <= 1799) {
                        annoTrovato = true;
                        break;
                    } else if (range == "prima-1700" && anno < 1700) {
                        annoTrovato = true;
                        break;
                    }
                }
                if (!annoTrovato) return false;
            }
        } else if (key == "lingua") {
            QString linguaMedia = QString::fromStdString(media->getLingua());
            if (!linguaMedia.contains(value.toString(), Qt::CaseInsensitive)) {
                return false;
            }
        } else if (key == "genere") {
            QString genereMedia = QString::fromStdString(media->getGenere());
            if (!genereMedia.contains(value.toString(), Qt::CaseInsensitive)) {
                return false;
            }
        } else if (key == "solo_disponibili" && value.toBool()) {
            if (!media->getDisponibilita()) {
                return false;
            }
        }
    }

    return true;
}




