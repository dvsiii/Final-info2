#ifndef PLATAFORMA_H
#define PLATAFORMA_H
#include "obstaculo.h"
class plataforma: public obstaculo
{
    float velocidad[2];
    float limites[2][2];
public:
    plataforma();
    float getvx();
    float getvy();
    float getl1x();
    float getl1y();
    float getl2x();
    float getl2y();
    void setv(float x, float y);
    void setl1(float x, float y);
    void setl2(float x, float y);
    void actualizar() override;
};

#endif // PLATAFORMA_H
