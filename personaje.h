#ifndef PERSONAJE_H
#define PERSONAJE_H
#include "entidad.h"

class personaje: public entidad
{
    float velocidad[2]; //[0]=x,[1]=y
    bool piso;
public:
    personaje();
    float getvx();
    float getvy();
    bool getp();
    void setp(bool p);
    void moverse(bool derecha, bool correr); //derecha positivo, izquierda negativo
    void saltar();
    void setv(float x, float y);
    void actualizar() override;
};

#endif // PERSONAJE_H
