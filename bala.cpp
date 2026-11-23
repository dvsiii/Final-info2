#include "bala.h"

bala::bala() {
    activo=false;
    velocidad[0]=0;
    velocidad[1]=0;
}
bool bala::getacti(){
    return activo;
}
float bala::getvx(){
    return velocidad[0];
}
float bala::getvy(){
    return velocidad[1];
}
void bala::setacti(bool estado){
    activo=estado;
}
void bala::setv(float x, float y){
    velocidad[0]=x;
    velocidad[1]=y;
}
void bala::actualizar(){
    if(activo==true){
        setx(getposicionx()+velocidad[0]);
        sety(velocidad[1]+getposiciony());
        velocidad[1]+=0.5f;
    }
}