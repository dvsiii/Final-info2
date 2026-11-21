#ifndef GANCHO_H
#define GANCHO_H
#include "obstaculo.h"
class gancho: public obstaculo
{
    float amplitud[2];
    float w;
    float equilibrio[2];
    float acumulado;
public:
    gancho();
    float getw();
    float getax();
    float getay();
    float getex();
    float getey();
    float getac();
    void sete(float x, float y);
    void setac(float t);
    void setw(float fa);
    void seta(float x, float y);
    void actualizar() override;
};
#endif // GANCHO_H
