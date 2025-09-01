#ifndef VISITORWIDGET_H
#define VISITORWIDGET_H

#include "Visitor.h"
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class Biblioteca;


class VisitorWidget : public QWidget, public Visitor
{
    Q_OBJECT
private:
    QWidget* widget;
    QHBoxLayout* mainLayout;
    QVBoxLayout* leftContainerLayout;
    QLabel* image;
    QHBoxLayout* pulsantieraLayout;
    QVBoxLayout* descrizioneLayout;
public:
    VisitorWidget(QWidget* parent = nullptr);
    QWidget* getWidget() const;
    void visit(Biblioteca* bibilioteca) override;
    //void visit(Multimedia* multimedia) override;
    void visit(Media_cartaceo* media_cartaceo) override;
    //void visit(Media_video* media_video) override;
    //void visit(Media_audio) override;
    //void visit(Periodico* periodico) override;
    void visit(Libro* libro) override;
    //void visit(Serie_tv* serie_tv) override;
    //void visit(Cd* cd) override;
    //void visit(Audiolibro* audiolibro) override;
    //void visit(Fumetto* fumetto) override;

};

#endif // VISITORWIDGET_H
