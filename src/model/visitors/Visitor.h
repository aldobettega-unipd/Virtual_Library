#ifndef VISITOR_H
#define VISITOR_H

class Biblioteca;
class Multimedia;
class Media_cartaceo;
class Media_video;
class Media_audio;
class Periodico;
class Libro;
class Cd;
class Audiolibro;

class Visitor
{
public:
    virtual ~Visitor() = default;
    virtual void visit(Biblioteca* bibilioteca) = 0;
    virtual void visit(Multimedia* multimedia) = 0;
    virtual void visit(Media_cartaceo* media_cartaceo) = 0;
    virtual void visit(Media_video* media_video) = 0;
    virtual void visit(Media_audio* media_audio) = 0;
    virtual void visit(Periodico* periodico) = 0;
    virtual void visit(Libro* libro) = 0;
    virtual void visit(Cd* cd) = 0;
    //virtual void visit(Audiolibro* audiolibro) = 0;
};

#endif // VISITOR_H
