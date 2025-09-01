#ifndef MEDIABOX_H
#define MEDIABOX_H

#include <QFrame>
#include <QLabel>

#include "../model/media/biblioteca.h"

class MediaBox : public QFrame
{
    Q_OBJECT
protected:
    Biblioteca* mediaItem;
    QLabel* imageLabel;
    QLabel* titleLabel;
    void mousePressEvent(QMouseEvent* event) override;

public:
    explicit MediaBox(Biblioteca* media, QWidget* parent = nullptr);
    virtual void setupUI();
    Biblioteca* getMediaItem() const;
    void updateImage();

signals:
    void clicked(Biblioteca* media);
};

#endif // MEDIABOX_H
