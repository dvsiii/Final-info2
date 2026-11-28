#ifndef SHERLOCK_H
#define SHERLOCK_H
#include "personaje.h"
class sherlock: public personaje
{
    bool gancho;
    float pivote[2];
    float fangular;
    float angulo;
    float espera;
    float tiempoEuforico;
    float tiempoCorriendo;
    float tiempoImpulsivo;
public:
    sherlock();
    bool getgancho();
    float getpivotex();
    float getpivotey();
    float getfa();
    float getangulo();
    float getespera();
    void setfa(float fa);
    void setangulo(float a);
    void setpivote(float x, float y);
    void setgancho(bool estado);
    void agarre(float px, float py);
    void activarEuforia();
    bool estaEuforico();
    bool estaImpulsivo();
    void moverse(bool derecha, bool correr);
    void saltar();
    void frenar();
    void soltarse();
    void actualizar() override;
};

#endif // SHERLOCK_H
