#include "gancho.h"
#include <QtMath>
gancho::gancho() {
    amplitud[0]=0;
    amplitud[1]=0;
    w=0;
    equilibrio[0]=0;
    equilibrio[1]=0;
    acumulado=0;
}
float gancho::getax(){
    return amplitud[0];
}
float gancho::getay(){
    return amplitud[1];
}
float gancho::getw(){
    return w;
}
float gancho::getex(){
    return equilibrio[0];
}
float gancho::getey(){
    return equilibrio[1];
}
float gancho::getac(){
    return acumulado;
}
void gancho::seta(float x, float y){
    amplitud[0]=x;
    amplitud[1]=y;
}
void gancho::setw(float fa){
    w=fa;
}
void gancho::sete(float x, float y){
    equilibrio[0]=x;
    equilibrio[1]=y;
}
void gancho::setac(float t){
    acumulado=t;
}
void gancho::actualizar(){
    setx(equilibrio[0]+amplitud[0]*qCos(w*acumulado));
    sety(equilibrio[1]+amplitud[1]*qSin(w*acumulado));
    acumulado+=0.016f;
}