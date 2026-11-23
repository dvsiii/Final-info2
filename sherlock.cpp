#include "sherlock.h"
#include <QtMath>
sherlock::sherlock() {
    gancho=false;
    pivote[0]=0;
    pivote[1]=0;
    angulo=0;
    fangular=0;
}
bool sherlock::getgancho(){
    return gancho;
}
float sherlock::getpivotex(){
    return pivote[0];
}
float sherlock::getpivotey(){
    return pivote[1];
}
float sherlock::getfa(){
    return fangular;
}
float sherlock::getangulo(){
    return angulo;
}
void sherlock::setfa(float fa){
    fangular=fa;
}
void sherlock::setangulo(float a){
    angulo=a;
}
void sherlock::setgancho(bool estado){
    gancho=estado;
}
void sherlock::setpivote(float x, float y){
    pivote[0]=x;
    pivote[1]=y;
}
void sherlock::agarre(float px, float py){
    setpivote(px,py);
    gancho=true;
    angulo=qAtan2(getposicionx()-px,getposiciony()-py);
    fangular=(getvx()/0.016f)/100.0f;
}
void sherlock::soltarse(){
    gancho=false;
    setp(false);
    setv(qCos(angulo)*fangular*0.016f*100.0f,-qSin(angulo)*fangular*0.016f*100.0f);
}
void sherlock::actualizar(){
    if(gancho==false){
        personaje::actualizar();
    }
    else{
        setx(pivote[0]+100.0f*qSin(angulo));
        sety(pivote[1]+100.0f*qCos(angulo));
        fangular=fangular+((-980.0f/100.0f)*qSin(angulo))*0.016f;
        angulo=angulo+fangular*0.016f;
    }
}