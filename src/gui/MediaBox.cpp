#include "MediaBox.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>

MediaBox::MediaBox(Biblioteca* media, QWidget* parent) : QFrame(parent), mediaItem(media), imageLabel(nullptr), titleLabel(nullptr) {
    setFrameStyle(QFrame::Box);
    setLineWidth(1);
    setupUI();

}

void MediaBox::setupUI() {
    if (imageLabel) {
        delete imageLabel;
        imageLabel = nullptr;
    }
    if (titleLabel) {
        delete titleLabel;
        titleLabel = nullptr;
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(5, 5, 5, 5);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: 1px solid; background-color: transparent;");
    imageLabel->setMinimumSize(200, 300);
    imageLabel->setScaledContents(false);

    titleLabel = new QLabel(QString::fromStdString(mediaItem->getTitolo()), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    titleLabel->setMargin(5);

    layout->addWidget(imageLabel, 1);
    layout->addWidget(titleLabel, 0);


    setLayout(layout);
    setContentsMargins(5, 5, 5, 5);

    updateImage();
}

void MediaBox::updateImage() {
    if (imageLabel && !mediaItem->getImmagine().empty()) {
        QString imagePath = QString::fromStdString(mediaItem->getImmagine());

        // Se il path non inizia con "./", lo aggiungiamo per chiarezza
        if (!imagePath.startsWith("./") && !imagePath.startsWith("/")) {
            imagePath = "./" + imagePath;
        }

        QPixmap pixmap;

        // Carica l'immagine con path relativo alla root del progetto
        pixmap.load(imagePath);

        if (!pixmap.isNull()) {
            QPixmap scaledPixmap = pixmap.scaled(imageLabel->size(),
                                                 Qt::KeepAspectRatioByExpanding,
                                                 Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
            qDebug() << "Image loaded successfully:" << imagePath;
        } else {
            imageLabel->setText("Image not found");
            qDebug() << "Failed to load image:" << imagePath;
        }
    } else if (imageLabel) {
        imageLabel->setText("No image");
    }
}


void MediaBox::mousePressEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    emit clicked(mediaItem);
    qDebug() << "MediaBox clicked:" << QString::fromStdString(mediaItem->getTitolo());
}
