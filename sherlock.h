#ifndef SHERLOCK_H
#define SHERLOCK_H
#include "personaje.h"
class sherlock: public personaje
{
    bool gancho;
    float pivote[2];
    float fangular;
    float angulo;
public:
    sherlock();
    bool getgancho();
    float getpivotex();
    float getpivotey();
    float getfa();
    float getangulo();
    void setfa(float fa);
    void setangulo(float a);
    void setpivote(float x, float y);
    void setgancho(bool estado);
    void agarre(float px, float py);
    void soltarse();
    void actualizar() override;
};

#endif // SHERLOCK_H
