#include "plataforma.h"

plataforma::plataforma() {
    velocidad[0]=0;
    velocidad[1]=0;
    limites[0][0]=0;
    limites[0][1]=0;
    limites[1][0]=0;
    limites[1][1]=0;
}
float plataforma::getvx(){
    return velocidad[0];
}
float plataforma::getvy(){
    return velocidad[1];
}
float plataforma::getl1x(){
    return limites[0][0];
}
float plataforma::getl1y(){
    return limites[0][1];
}
float plataforma::getl2x(){
    return limites[1][0];
}
float plataforma::getl2y(){
    return limites[1][1];
}
void plataforma::setv(float x, float y){
    velocidad[0]=x;
    velocidad[1]=y;
}
void plataforma::setl1(float x, float y){
    limites[0][0]=x;
    limites[0][1]=y;
}
void plataforma::setl2(float x, float y){
    limites[1][0]=x;
    limites[1][1]=y;
}
void plataforma::actualizar(){
    setx(getposicionx()+velocidad[0]);
    if(getposicionx()<=limites[0][0]&&velocidad[0]<0){
        velocidad[0]=velocidad[0]*-1;
    }
    if(getposicionx()>=limites[1][0]&&velocidad[0]>0){
        velocidad[0]=velocidad[0]*-1;
    }
    sety(velocidad[1]+getposiciony());
    if(getposiciony()<=limites[0][1]&&velocidad[1]<0){
        velocidad[1]=velocidad[1]*-1;
    }
    if(getposiciony()>=limites[1][1]&&velocidad[1]>0){
        velocidad[1]=velocidad[1]*-1;
    }
}