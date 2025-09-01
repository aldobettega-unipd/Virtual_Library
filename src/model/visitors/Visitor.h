#ifndef VISITOR_H
#define VISITOR_H

class Biblioteca;
class Multimedia;
class Media_cartaceo;
class Media_video;
class Media_audio;
class Periodico;
class Libro;
class Serie_tv;
class Cd;
class Audiolibro;
class Fumetto;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(Biblioteca* bibilioteca) = 0;
    //virtual void visit(Multimedia* multimedia) = 0;
    virtual void visit(Media_cartaceo* media_cartaceo) = 0;
    //virtual void visit(Media_video* media_video) = 0;
    //virtual void visit(Media_audio) = 0;
    //virtual void visit(Periodico* periodico) = 0;
    virtual void visit(Libro* libro) = 0;
    //virtual void visit(Serie_tv* serie_tv) = 0;
    //virtual void visit(Cd* cd) = 0;
    //virtual void visit(Audiolibro* audiolibro) = 0;
    //virtual void visit(Fumetto* fumetto) = 0;
};

#endif // VISITOR_H
