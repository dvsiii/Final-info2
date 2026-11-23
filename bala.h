#ifndef BALA_H
#define BALA_H
#include "entidad.h"
class bala: public entidad
{
    bool activo;
    float velocidad[2];
public:
    bala();
    bool getacti();
    void setacti(bool estado);
    float getvx();
    float getvy();
    void setv(float x,float y);
    void actualizar() override;
};

#endif // BALA_H
