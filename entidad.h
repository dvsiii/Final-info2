#ifndef ENTIDAD_H
#define ENTIDAD_H
#include <string>
class entidad
{
    float posicion[2];
    float hitbox[2];
    std::string sprite;
public:
    entidad();
    virtual void actualizar()=0;
    virtual bool colision(entidad* otra);
    virtual ~entidad();
    float getposicionx();
    float getposiciony();
    float gethitboxb();
    float gethitboxa();
    std::string getsprite();
    void setx(float x);
    void sety(float y);
    void setb(float b);
    void seta(float a);
    void sets(std::string s);
};

#endif // ENTIDAD_H
