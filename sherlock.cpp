#include "sherlock.h"
#include <QtMath>
sherlock::sherlock() {
    gancho=false;
    pivote[0]=0;
    pivote[1]=0;
    angulo=0;
    fangular=0;
    espera=0;
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
float sherlock::getespera(){
    return espera;
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
    angulo=qAtan2((getposicionx()+16.0f)-px,(getposiciony()+16.0f)-py);
    fangular=(getvx()/0.016f)/50.0f;
}
void sherlock::soltarse(){
    gancho=false;
    setp(false);
    espera=0.3f;
    setv(qCos(angulo)*fangular*0.016f*50.0f,(-qSin(angulo)*fangular*0.016f*50.0f)-12.5);
}
void sherlock::actualizar(){
    if(gancho==false){
        if(espera>=0){
            espera-=0.016f;
        }
        personaje::actualizar();
    }
    else{
        setx(pivote[0]+50.0f*qSin(angulo)-16.0f);
        sety(pivote[1]+50.0f*qCos(angulo)-16.0f);
        fangular=fangular+((-980.0f/50.0f)*qSin(angulo))*0.016f;
        fangular *= 0.95f;
        angulo=angulo+fangular*0.016f;
        if(angulo>1.5f){
            angulo=1.5f;
            fangular=0;
        }
        else if(angulo<-1.5f){
            angulo=-1.5f;
            fangular=0;
        }
    }
}