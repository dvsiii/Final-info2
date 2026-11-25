#include "puerta.h"

puerta::puerta() {
    tiempo=0;
    duracion=0;
    boton[0]=0;
    boton[1]=0;
    pboton[0]=0;
    pboton[1]=0;
}
float puerta::gettiempo(){
    return tiempo;
}
float puerta::getd(){
    return duracion;
}
float puerta::getbl(){
    return boton[0];
}
float puerta::getba(){
    return boton[1];
}
float puerta::getpbx(){
    return pboton[0];
}
float puerta::getpby(){
    return pboton[1];
}
void puerta::settiempo(float t){
    tiempo=t;
}
void puerta::setd(float du){
    duracion=du;
}
void puerta::setboton(float l, float a){
    boton[0]=l;
    boton[1]=a;
}
void puerta::setpboton(float x, float y){
    pboton[0]=x;
    pboton[1]=y;
}
bool puerta::tocoboton(entidad* otra){
    if(otra==nullptr){
        return false;
    }
    if(boton[1]!=0&&otra->gethitboxa()!=0){
        if(boton[0]+pboton[0]>otra->getposicionx()&&pboton[0]<otra->gethitboxb()+otra->getposicionx()){
            if(boton[1]+pboton[1]>otra->getposiciony()&&pboton[1]<otra->gethitboxa()+otra->getposiciony()){
                return true;
            }
        }
    }
    else if(boton[1]!=0&&otra->gethitboxa()==0){
        float cercaX=otra->getposicionx();
        float cercaY=otra->getposiciony();
        if(cercaX<pboton[0]) {
            cercaX=pboton[0];
        }
        else if(cercaX>pboton[0]+boton[0]){
            cercaX=pboton[0]+boton[0];
        }
        if(cercaY<pboton[1]){
            cercaY=pboton[1];
        }
        else if(cercaY>pboton[1]+boton[1]){
            cercaY=pboton[1]+boton[1];
        }
        float dx=cercaX-otra->getposicionx();
        float dy=cercaY-otra->getposiciony();
        if(dx*dx+dy*dy<=otra->gethitboxb()*otra->gethitboxb()){
            return true;
        }
    }
    return false;
}
void puerta::activar(bool presionado){
    if(presionado==true){
        tiempo=duracion;
        setactivo(false);
    }
}
void puerta::actualizar(){
    if(getactivo()==false){
        tiempo-=0.016f;
        if(tiempo<=0){
            setactivo(true);
        }
    }
}