#include "MediaBox.h"
#include <QVBoxLayout>
#include <QDebug>

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
    layout->setContentsMargins(0, 0, 0, 0);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: 1px solid; background-color: transparent;");
    imageLabel->setMinimumSize(200, 300);
    imageLabel->setScaledContents(false);

    titleLabel = new QLabel(QString::fromStdString(mediaItem->getTitolo()), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setWordWrap(true);
    titleLabel->setMaximumWidth(150);
    titleLabel->setMargin(1);

    layout->addWidget(imageLabel, 1);
    layout->addWidget(titleLabel, 0);

    setLayout(layout);
    setContentsMargins(0, 0, 0, 0);

    updateImage();
}

void MediaBox::updateImage() {
    if (imageLabel && !mediaItem->getImmagine().empty()) {
        QPixmap pixmap(QString::fromStdString(mediaItem->getImmagine()));
        if (!pixmap.isNull()) {
            // Scala l'immagine mantenendo le proporzioni e riempiendo tutto lo spazio
            QPixmap scaledPixmap = pixmap.scaled(imageLabel->size(),
                                                 Qt::KeepAspectRatioByExpanding,
                                                 Qt::SmoothTransformation);
            imageLabel->setPixmap(scaledPixmap);
        } else {
            imageLabel->setText("No image");
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
