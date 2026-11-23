#ifndef NIVEL_H
#define NIVEL_H

class nivel
{
    short int dificultad;
    bool completado;
public:
    nivel();
    short int getdificultad();
    void setdificultad(short int);
    bool getcompletado();
    void setcompletado(bool estado);
    virtual void actualizar()=0;
    virtual ~nivel();
};

#endif // NIVEL_H
