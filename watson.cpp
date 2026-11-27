#include "watson.h"
#include <QtMath>
using namespace std;
watson::watson() {
    control=false;
    dsherlock[0]=0;
    dsherlock[1]=0;
    pistas=nullptr;
}
bool watson::getcontrol(){
    return control;
}
float watson::getdx(){
    return dsherlock[0];
}
float watson::getdy(){
    return dsherlock[1];
}
void watson::setcontrol(bool estado){
    control=estado;
}
void watson::setdsh(float x, float y){
    dsherlock[0]=x;
    dsherlock[1]=y;
}
void watson::setpista(pista* p){
    pistas=p;
}
bala* watson::disparar(float x, float y){
    bala* eso=new bala;
    float angulo=qAtan2(y-getposiciony(),x-getposicionx());
    eso->setx(getposicionx());
    eso->sety(getposiciony());
    eso->setv(15.0f*qCos(angulo),15.0f*qSin(angulo));
    eso->setacti(true);
    return eso;
}
string watson::pistacerca(){
    string direccionx="";
    string direcciony="";
    if(pistas==nullptr){
        string mensaje="no hay pista disponible";
        return mensaje;
    }
    if(pistas->getposicionx()>getposicionx()){
        direccionx+="derecha";
    }
    else if(pistas->getposicionx()<getposicionx()){
        direccionx+="izquierda";
    }
    if(pistas->getposiciony()<getposiciony()){
        direcciony+="arriba";
    }
    else if(pistas->getposiciony()>getposiciony()){
        direcciony+="abajo";
    }
    string mensaje="la pista mas cerca esta "+direcciony+" a la "+direccionx;
    return mensaje;
}
void watson::actualizar(){
    if(control==false){
        float dx=dsherlock[0]-getposicionx();
        if(dx>120){
            moverse(true,true);
        }
        else if(dx>60){
            moverse(true,false);
        }
        else if(dx<-120){
            moverse(false,true);
        }
        else if(dx<-60) {
            moverse(false,false);
        }
        else{
            setv(0,getvy());
        }
        if(dsherlock[1]-getposiciony()>60){
            sety(dsherlock[1]);
        }
        else if(dsherlock[1]-getposiciony()<-60){
            sety(dsherlock[1]);
        }
    }
    personaje::actualizar();
}