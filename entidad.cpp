#include "entidad.h"
using namespace std;
entidad::entidad(){
    posicion[0]=0;
    posicion[1]=0;
    hitbox[0]=0;
    hitbox[1]=0;
    sprite="";
}
string entidad::getsprite(){
    return sprite;
}
float entidad::gethitboxa(){
    return hitbox[1];
}
float entidad::gethitboxb(){
    return hitbox[0];
}
float entidad::getposicionx(){
    return posicion[0];
}
float entidad::getposiciony(){
    return posicion[1];
}
void entidad::seta(float a){
    hitbox[1]=a;
}
void entidad::setb(float b){
    hitbox[0]=b;
}
void entidad::setx(float x){
    posicion[0]=x;
}
void entidad::sety(float y){
    posicion[1]=y;
}
void entidad::sets(string s){
    sprite=s;
}
bool entidad::colision(entidad* otra){
    if(otra==nullptr){
        return false;
    }
    if(hitbox[1]!=0&&otra->gethitboxa()!=0){
        if(hitbox[0]+posicion[0]>otra->getposicionx()&&posicion[0]<otra->gethitboxb()+otra->getposicionx()){
            if(hitbox[1]+posicion[1]>otra->getposiciony()&&posicion[1]<otra->gethitboxa()+otra->getposiciony()){
                return true;
            }
        }
    }
    else if(hitbox[1]!=0&&otra->gethitboxa()==0){
        float cercaX=otra->getposicionx();
        float cercaY=otra->getposiciony();
        if(cercaX<posicion[0]) {
            cercaX=posicion[0];
        }
        else if(cercaX>posicion[0]+hitbox[0]){
            cercaX=posicion[0]+hitbox[0];
        }
        if(cercaY<posicion[1]){
            cercaY=posicion[1];
        }
        else if(cercaY>posicion[1]+hitbox[1]){
            cercaY=posicion[1]+hitbox[1];
        }
        float dx=cercaX-otra->getposicionx();
        float dy=cercaY-otra->getposiciony();
        if(dx*dx+dy*dy<=otra->gethitboxb()*otra->gethitboxb()){
            return true;
        }
    }
    else if(hitbox[1]==0&&otra->gethitboxa()!=0){
        return otra->colision(this);
    }
    return false;
}
entidad::~entidad(){

}