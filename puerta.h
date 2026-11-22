#ifndef PUERTA_H
#define PUERTA_H
#include "obstaculo.h"
class puerta: public obstaculo
{
    float tiempo;
    float pboton[2];
    float boton[2];
    float duracion;
public:
    puerta();
    float gettiempo();
    float getpbx();
    float getpby();
    float getbl();
    float getba();
    float getd();
    void settiempo(float t);
    void setd(float du);
    void setpboton(float x, float y);
    void setboton(float l, float a);
    void activar(bool pressionado);
    void actualizar() override;
};
#endif // PUERTA_H
