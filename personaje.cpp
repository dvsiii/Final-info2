#include "personaje.h"

personaje::personaje() {
    velocidad[0]=0;
    velocidad[1]=0;
    piso=true;
}
float personaje::getvx(){
    return velocidad[0];
}
float personaje::getvy(){
    return velocidad[1];
}
bool personaje::getp(){
    return piso;
}
void personaje::setv(float x, float y){
    velocidad[0]=x;
    velocidad[1]=y;
}
void personaje::setp(bool p){
    piso=p;
}
void personaje::moverse(bool derecha, bool correr){
    if(derecha==true){
        if(correr==true){
            velocidad[0]=10;
        }
        else{
            velocidad[0]=5;
        }
    }
    else{
        if(correr==true){
            velocidad[0]=-10;
        }
        else{
            velocidad[0]=-5;
        }
    }
}
void personaje::saltar(){
    if(piso==true){
        velocidad[1]=-5;
        piso=false;
    }
}
void personaje::actualizar(){
    setx(getposicionx()+velocidad[0]);
    if(piso==true){
        velocidad[1]=0;
    }
    sety(velocidad[1]+getposiciony());
    if(piso==false){
        velocidad[1]+=1;
    }
}