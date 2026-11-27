#include "nivel2.h"
#include <QtMath>
#include <algorithm>
nivel2::nivel2() {
    jugador.setcontrol(true);
    jugador.setx(400);
    jugador.sety(300);
    jugador.seta(32);
    jugador.setb(32);
    selecionado=-1;
    muebles[0].setx(230);
    muebles[0].sety(300);
    muebles[0].setb(50);
    muebles[0].seta(50);
    muebles[1].setx(630);
    muebles[1].sety(300);
    muebles[1].setb(50);
    muebles[1].seta(50);
    nota[0].setid(6);
    nota[1].setid(4);
    nota[2].setid(5);
    nota[3].setid(2);
    nota[4].setid(3);
    nota[5].setid(1);
    pared[0].setx(0);
    pared[0].sety(0);
    pared[0].setb(800);
    pared[0].seta(72);
    pared[1].setx(0);
    pared[1].sety(0);
    pared[1].setb(44);
    pared[1].seta(600);
    pared[2].setx(0);
    pared[2].sety(501);
    pared[2].setb(800);
    pared[2].seta(99);
    pared[3].setx(759);
    pared[3].sety(0);
    pared[3].setb(41);
    pared[3].seta(600);
}
watson& nivel2::getjugador(){
    return jugador;
}
short int nivel2::getselecionado(){
    return selecionado;
}
std::array<plataforma,2>& nivel2::getmuebles(){
    return muebles;
}
std::array<notas,6>& nivel2::getnotas(){
    return nota;
}
bool nivel2::cercamueble(float xm,float ym){
    float dx=jugador.getposicionx()-xm;
    float dy=jugador.getposiciony()-ym;
    float dist=qSqrt(dx * dx + dy * dy);
    if(dist<=70.0f){
        return true;
    }
    else{
        return false;
    }
}
void nivel2::seleccionar(int in){
    if(selecionado==-1){
        selecionado=in;
    }
    else{
        short int p=nota[in].getid();
        nota[in].setid(nota[selecionado].getid());
        nota[selecionado].setid(p);
        selecionado=-1;
    }
    bool completado;
    if(nota[0].getid()==1&&nota[1].getid()==2&&nota[2].getid()==3&&nota[5].getid()==6&&nota[3].getid()==4&&nota[4].getid()==5){
        completado=true;
    }
    else{
        completado=false;
    }
    setcompletado(completado);
}
void nivel2::resolverColision(personaje& p, plataforma& bloque){
    float penIzq=(p.getposicionx()+p.gethitboxb())-bloque.getposicionx();
    float penDer=(bloque.getposicionx()+bloque.gethitboxb())-p.getposicionx();
    float penArriba=(p.getposiciony()+p.gethitboxa())-bloque.getposiciony();
    float penAbajo=(bloque.getposiciony()+bloque.gethitboxa())-p.getposiciony();
    if(std::min(penIzq, penDer)<std::min(penArriba, penAbajo)){
        if(penIzq<penDer){
            p.setx(bloque.getposicionx()-p.gethitboxb());
            p.setv(0,p.getvy());
        }
        else{
            p.setx(bloque.getposicionx()+bloque.gethitboxb());
            p.setv(0,p.getvy());
        }
    }
    else{
        if (penArriba<penAbajo){
            p.sety(bloque.getposiciony()-p.gethitboxa());
            p.setv(p.getvx(),0);
        }
        else {
            p.sety(bloque.getposiciony()+bloque.gethitboxa());
            p.setv(p.getvx(),0);
        }
    }
}
void nivel2::actualizar(){
    jugador.actualizar();
    for(int i=1;i>=0;i--){
        if(jugador.colision(&muebles[i])==true){
            resolverColision(jugador,muebles[i]);
        }
    }
    for(int i=3;i>=0;i--){
        if(jugador.colision(&pared[i])==true){
            resolverColision(jugador,pared[i]);
        }
    }
}