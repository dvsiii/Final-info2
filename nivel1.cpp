#include "nivel1.h"
#include <QtMath>
nivel1::nivel1(short int dif) {
    setdificultad(dif);
    objetivo=0;
    jugador.setb(32);
    jugador.seta(32);
    jugador.setx(1200);
    jugador.sety(1718);
    agente.seta(32);
    agente.setb(32);
    agente.setx(1150);
    agente.sety(1718);
    plataforma piso;
    piso.seta(50);
    piso.setb(2400);
    piso.setx(0);
    piso.sety(1750);
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
    if(objetivo==6){
        setcompletado(true);
        return;
    }
    agente.setdsh(jugador.getposicionx(),jugador.getposiciony());
    agente.actualizar();
    jugador.actualizar();
    puert.actualizar();
    jugador.setp(false);
    agente.setp(false);
    for(int i=plataformas.size()-1;i>=0;i--){
        plataformas[i].actualizar();
        if(jugador.colision(&plataformas[i])==true){
            if(jugador.getvy()>=0){
                jugador.setv(jugador.getvx(),0);
                jugador.sety(plataformas[i].getposiciony()-jugador.gethitboxa());
                jugador.setp(true);
            }
        }
        if(agente.colision(&plataformas[i])==true){
            if(agente.getvy()>=0){
                agente.setv(agente.getvx(),0);
                agente.sety(plataformas[i].getposiciony()-agente.gethitboxa());
                agente.setp(true);
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
    pista* cercana =nullptr;
    float distmin=99999;
    for(int i=pistas.size()-1;i>=0;i--){
        pistas[i].actualizar();
        if(jugador.colision(&pistas[i])==true&&pistas[i].getrecolectado()==false){
            pistas[i].setrecolectado(true);
            objetivo++;
        }
        if(distmin>qSqrt(qPow((pistas[i].getposicionx()-agente.getposicionx()),2)+qPow((pistas[i].getposiciony()-agente.getposiciony()),2))&&pistas[i].getrecolectado()==false){
            distmin=qSqrt(qPow((pistas[i].getposicionx()-agente.getposicionx()),2)+qPow((pistas[i].getposiciony()-agente.getposiciony()),2));
            cercana=&pistas[i];
        }
    }
    agente.setpista(cercana);
    for(int i=balas.size()-1;i>=0;i--){
        if(balas[i]->getacti()==true){
            balas[i]->actualizar();
            for(int j=plataformas.size()-1;j>=0;j--){
                if(balas[i]->colision(&plataformas[j])){
                    balas[i]->setacti(false);
                }
            }
            if(balas[i]->getposicionx()<0||balas[i]->getposicionx()>2400){
                balas[i]->setacti(false);
            }
            if(balas[i]->getposiciony()<0||balas[i]->getposiciony()>1800){
                balas[i]->setacti(false);
            }
            if(puert.tocoboton(balas[i])==true){
                balas[i]->setacti(false);
                puert.activar(true);
            }
        }
        else{
            delete balas[i];
            balas.erase(balas.begin()+i);
        }
    }
    if(puert.getactivo()==true){
        if(jugador.colision(&puert)==true){
            jugador.setv(0,jugador.getvy());
            jugador.setx(puert.getposicionx()+puert.gethitboxb());
        }
    }
}
nivel1::~nivel1(){
    for(int i=balas.size()-1;i>=0;i--){
        delete balas[i];
    }
    balas.clear();
}