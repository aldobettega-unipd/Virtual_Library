#ifndef VISITORWIDGET_H
#define VISITORWIDGET_H

#include "Visitor.h"
#include <QWidget>
#include <QPixmap>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>

class Biblioteca;


class VisitorWidget : public QWidget, public Visitor
{
    Q_OBJECT
private:
    QWidget* widget;
    QHBoxLayout* mainLayout;
    QLabel* image;
    QWidget* descrizioneContainer;
    QFormLayout* descrizioneLayout;
public:
    VisitorWidget(QWidget* parent = nullptr);
    QWidget* getWidget() const;
    void visit(Biblioteca* bibilioteca) override;
    void visit(Multimedia* multimedia) override;
    void visit(Media_cartaceo* media_cartaceo) override;
    void visit(Media_video* media_video) override;
    void visit(Media_audio* media_audio) override;
    void visit(Periodico* periodico) override;
    void visit(Libro* libro) override;
    void visit(Cd* cd) override;
    //void visit(Audiolibro* audiolibro) override;
};

#endif // VISITORWIDGET_H
