#include "watson.h"
#include <QtMath>
using namespace std;
watson::watson() {
    control=false;
    dsherlock[0]=0;
    dsherlock[1]=0;
    pistas=nullptr;
    ultimaPista=nullptr;
    consultasMismaPista=0;
    decisionMov=0;
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
    if (pistas==nullptr) {
        return"no hay pista disponible";
    }
    aprender();
    string direccionx=(pistas->getposicionx()>getposicionx())?"derecha":"izquierda";
    string direcciony=(pistas->getposiciony()<getposiciony())?"arriba":"abajo";
    string mensaje="Pista "+direcciony+" a la "+direccionx;
    if (consultasMismaPista==2){
        int dist=qSqrt(qPow(pistas->getposicionx()-getposicionx(),2)+qPow(pistas->getposiciony()-getposiciony(),2));
        mensaje+=" (~"+to_string(dist)+" px)";
    } else if(consultasMismaPista>=3){
        mensaje+=" en ("+to_string((int)pistas->getposicionx())+", "+to_string((int)pistas->getposiciony())+")";
    }
    return mensaje;
}
void watson::moversevertical(bool arriba, bool correr){
    if(arriba==true){
        if(correr==true){
            setv(getvx(),-8);
        }
        else{
            setv(getvx(),-4);
        }
    }
    else{
        if(correr==true){
            setv(getvx(),8);
        }
        else{
            setv(getvx(),4);
        }
    }
}
void watson::percibir(float sx, float sy, pista* p){
    dsherlock[0]=sx;
    dsherlock[1]=sy;
    pistas=p;
}
void watson::aprender(){
    if (pistas==nullptr){
        return;
    }
    if(pistas==ultimaPista){
        consultasMismaPista++;
    }
    else{
        ultimaPista=pistas;
        consultasMismaPista=1;
    }
}
void watson::razonar(){
    float dx=dsherlock[0]-getposicionx();
    if(dx>120)decisionMov=2;
    else if(dx>60)decisionMov=1;
    else if(dx<-120)decisionMov=-2;
    else if(dx<-60)decisionMov=-1;
    else decisionMov=0;
}

void watson::actuar(){
    if(decisionMov==2)moverse(true, true);
    else if(decisionMov==1)moverse(true, false);
    else if(decisionMov==-2)moverse(false, true);
    else if(decisionMov==-1)moverse(false, false);
    else setv(0,getvy());
    if (dsherlock[1]-getposiciony()>60||dsherlock[1]-getposiciony()<-60){
        sety(dsherlock[1]);
    }
    personaje::actualizar();
}
void watson::actualizar(){
    if(control==false){
        razonar();
        actuar();
    }
    else{
        setx(getposicionx()+getvx());
        sety(getvy()+getposiciony());
    }
}