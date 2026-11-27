#ifndef WATSON_H
#define WATSON_H
#include "personaje.h"
#include "pista.h"
#include "bala.h"
#include <string>
class watson: public personaje
{
    bool control;
    float dsherlock[2];
    pista* pistas;
public:
    watson();
    bool getcontrol();
    void setcontrol(bool estado);
    float getdx();
    float getdy();
    bala* disparar(float x, float y);
    void setpista(pista* p);
    void moversevertical(bool arriba, bool correr);
    std::string pistacerca();
    void setdsh(float dx, float dy);
    void actualizar() override;
};

#endif // WATSON_H
