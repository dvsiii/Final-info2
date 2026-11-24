#include "nivel1.h"

nivel1::nivel1(short int dif) {
    setdificultad(dif);
    jugador.setb(32);
    jugador.seta(32);
    jugador.setx(1200);
    jugador.sety(568);
    agente.seta(32);
    agente.setb(32);
    agente.setx(1150);
    agente.sety(568);
    plataforma piso;
    piso.seta(50);
    piso.setb(2400);
    piso.setx(0);
    piso.sety(600);
    plataformas.push_back(piso);
    if(dif==0){ //Modo facil

    }
    else if(dif==1){ //Modo normal

    }
    else if(dif==2){ //Modo Dificil
    }
}
sherlock& nivel1::getjugador(){
    return jugador;
}
watson& nivel1::getagente(){
    return agente;
}
void nivel1::agregarbala(bala* b){
    balas.push_back(b);
}
void nivel1::actualizar(){
    agente.setdsh(jugador.getposicionx(),jugador.getposiciony());
    agente.actualizar();
    jugador.actualizar();
    puert.actualizar();
    jugador.setp(false);
    agente.setp(false);
    for(int i=plataformas.size()-1;i>=0;i--){
        plataformas[i].actualizar();
        if(jugador.colision(&plataformas[i])==true){
            jugador.setp(true);
            if(jugador.getvy()>0){
                jugador.setv(jugador.getvx(),0);
            }
        }
        if(agente.colision(&plataformas[i])==true){
            agente.setp(true);
            if(agente.getvy()>0){
                agente.setv(agente.getvx(),0);
            }
        }
    }
    if(getdificultad()==2){
        for(int i=ganchos.size()-1;i>=0;i--){
            ganchos[i].actualizar();
            if(jugador.colision(&ganchos[i])==true&&jugador.getgancho()==false){
                jugador.agarre(ganchos[i].getex(),ganchos[i].getey());
            }
        }
    }
    for(int i=pistas.size()-1;i>=0;i--){
        pistas[i].actualizar();
        if(jugador.colision(&pistas[i])==true){
            pistas[i].setrecolectado(true);
        }
    }
    for(int i=balas.size()-1;i>=0;i--){
        balas[i]->actualizar();
    }
}
nivel1::~nivel1(){
    for(int i=balas.size()-1;i>=0;i--){
        delete balas[i];
    }
    balas.clear();
}