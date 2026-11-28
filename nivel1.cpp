#include "nivel1.h"
#include <QtMath>
#include <algorithm>
using namespace std;
nivel1::nivel1(short int dif){
    if (dif<0||dif>2){
        throw invalid_argument("Dificultad invalida: debe ser 0, 1 o 2.");
    }
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
    piso[0].seta(50);
    piso[0].setb(2400);
    piso[0].setx(0);
    piso[0].sety(1750);
    piso[1].seta(1);
    piso[1].setb(549);
    piso[1].setx(4);
    piso[1].sety(1119);
    piso[2].seta(1);
    piso[2].setb(473);
    piso[2].setx(772);
    piso[2].sety(1372);
    piso[3].seta(1);
    piso[3].setb(305);
    piso[3].setx(1544);
    piso[3].sety(1160);
    piso[4].seta(1);
    piso[4].setb(544);
    piso[4].setx(1852);
    piso[4].sety(140);
    piso[5].seta(1800);
    piso[5].setb(1);
    piso[5].setx(0);
    piso[5].sety(0);
    piso[6].seta(1800);
    piso[6].setb(1);
    piso[6].setx(2400);
    piso[6].sety(0);
    pistas[0].setx(1300);
    pistas[0].sety(1720);
    pistas[0].setpistay(1720);
    pistas[0].seta(24);
    pistas[0].setb(24);
    pistas[1].setx(2100);
    pistas[1].sety(130);
    pistas[1].setpistay(130);
    pistas[1].seta(24);
    pistas[1].setb(24);
    pistas[2].setx(2369);
    pistas[2].sety(1720);
    pistas[2].setpistay(1720);
    pistas[2].seta(24);
    pistas[2].setb(24);
    pistas[3].setx(12);
    pistas[3].sety(1720);
    pistas[3].setpistay(1720);
    pistas[3].seta(24);
    pistas[3].setb(24);
    pistas[4].setx(192);
    pistas[4].sety(1108);
    pistas[4].setpistay(1108);
    pistas[4].seta(24);
    pistas[4].setb(24);
    pistas[5].setx(932);
    pistas[5].sety(1361);
    pistas[5].setpistay(1361);
    pistas[5].seta(24);
    pistas[5].setb(24);
    if(dif==0){ //Modo facil
        plataforma p;
        p.setx(2000);
        p.sety(1700);
        p.seta(15);
        p.setb(50);
        p.setl2(2000,1731);
        p.setl1(2000,140);
        p.setv(0,10);
        plataformas.push_back(p);
        p.setx(300);
        p.sety(1700);
        p.seta(15);
        p.setb(50);
        p.setl2(300,1731);
        p.setl1(300,1119);
        plataformas.push_back(p);
    }
    else if(dif==1){ //Modo normal
        plataforma p;
        p.setx(1849);
        p.sety(1700);
        p.seta(15);
        p.setb(50);
        plataformas.push_back(p);
        p.setx(2096);
        p.sety(1550);
        p.setl1(2096,1450);
        p.setl2(2096,1590);
        p.setv(0,3);
        plataformas.push_back(p);
        p.setx(1850);
        p.sety(1340);
        p.setl2(2250,1340);
        p.setl1(1849,1340);
        p.setv(3,0);
        plataformas.push_back(p);
        p.setx(2260);
        p.sety(1323);
        p.seta(10);
        p.setb(40);
        p.setv(0,0);
        plataformas.push_back(p);
        p.setx(2350);
        p.sety(1190);
        p.setl1(2350,900);
        p.setl2(2350,1190);
        p.setv(0,3);
        plataformas.push_back(p);
        p.setx(2350);
        p.sety(880);
        p.setl1(2000,530);
        p.setl2(2350,880);
        p.setv(3,3);
        plataformas.push_back(p);
        p.setx(1900);
        p.sety(530);
        p.seta(10);
        p.setb(60);
        p.setv(0,0);
        plataformas.push_back(p);
        p.setx(2050);
        p.sety(500);
        p.setl1(2050,300);
        p.setl2(2050,500);
        p.setv(0,3);
        plataformas.push_back(p);
        p.setx(2000);
        p.sety(280);
        p.setl1(2000,160);
        p.setl2(2120,280);
        p.setv(3,3);
        plataformas.push_back(p);
        p.setv(0,0);
        p.setx(500);
        p.sety(1600);
        p.seta(20);
        p.setb(60);
        plataformas.push_back(p);
        p.setx(350);
        p.sety(1450);
        plataformas.push_back(p);
        p.setx(150);
        p.sety(1350);
        plataformas.push_back(p);
        p.setx(200);
        p.sety(1250);
        plataformas.push_back(p);
        puert.setb(50);
        puert.seta(95);
        puert.setx(1);
        puert.sety(1637);
        puert.setboton(12,16);
        puert.setpboton(1232,1152);
        puert.setd(30);
    }
    else if(dif==2){ //Modo Dificil
        puert.setb(50);
        puert.seta(95);
        puert.setx(1);
        puert.sety(1637);
        puert.setboton(12,16);
        puert.setpboton(1232,1152);
        puert.setd(30);
        plataforma p;
        gancho g;
        p.setx(1849);
        p.sety(1700);
        p.seta(15);
        p.setb(50);
        plataformas.push_back(p);
        p.setx(2096);
        p.sety(1550);
        p.setl1(2096,1450);
        p.setl2(2096,1590);
        p.setv(0,3);
        plataformas.push_back(p);
        g.sete(1950,1340);
        g.setx(1950);
        g.sety(1340);
        g.setb(20);
        g.seta(0,0);
        g.setw(0);
        g.setac(0);
        ganchos.push_back(g);
        p.setx(2350);
        p.sety(1200);
        p.setv(0,0);
        p.setb(50);
        p.seta(20);
        plataformas.push_back(p);
        g.sete(2000,1050);
        g.setx(2000);
        g.sety(1050);
        g.setb(20);
        g.seta(40,20);
        g.setw(2);
        g.setac(3);
        ganchos.push_back(g);
        g.sete(2310,840);
        g.setx(2310);
        g.sety(840);
        g.setb(25);
        g.seta(0,0);
        g.setw(0);
        g.setac(0);
        ganchos.push_back(g);
        p.setx(1900);
        p.sety(700);
        plataformas.push_back(p);
        p.setx(2100);
        p.sety(600);
        p.setl1(2100,400);
        p.setl2(2300,600);
        p.setv(3,3);
        plataformas.push_back(p);
        p.setx(2000);
        p.sety(350);
        p.setv(0,3);
        p.setl1(2000,250);
        p.setl2(2000,350);
        plataformas.push_back(p);
        p.setv(0,0);
        p.setx(500);
        p.sety(1600);
        p.seta(20);
        p.setb(60);
        plataformas.push_back(p);
        p.setx(350);
        p.sety(1450);
        plataformas.push_back(p);
        p.setx(150);
        p.sety(1350);
        plataformas.push_back(p);
        p.setx(200);
        p.sety(1250);
        plataformas.push_back(p);
        puert.setb(50);
        puert.seta(95);
        puert.setx(1);
        puert.sety(1637);
        puert.setboton(12,16);
        puert.setpboton(1232,1152);
        puert.setd(30);
    }
}
sherlock& nivel1::getjugador(){
    return jugador;
}
watson& nivel1::getagente(){
    return agente;
}
array<pista,6>& nivel1::getpistas(){
    return pistas;
}
vector<plataforma>& nivel1::getplataformas(){
    return plataformas;
}
vector<gancho>& nivel1::getganchos(){
    return ganchos;
}
vector<bala*>& nivel1::getbalas(){
    return balas;
}
puerta& nivel1::getpuerta(){
    return puert;
}
void nivel1::agregarbala(bala* b){
    balas.push_back(b);
}
void nivel1::resolverColision(personaje& p, plataforma& bloque){
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
        if(penArriba<penAbajo&&p.getvy()>=0){
            p.setx(p.getposicionx()+bloque.getvx());
            if(bloque.getvy()>0){
                p.setv(p.getvx(),bloque.getvy());
            }
            else{
                p.setv(p.getvx(),0);
            }
            p.sety(bloque.getposiciony()-p.gethitboxa());
            p.setp(true);
        }
    }
}
void nivel1::actualizar(){
    if(objetivo==6){
        setcompletado(true);
        return;
    }
    pista* cercana=nullptr;
    float distmin=99999;
    for(int i = pistas.size()-1;i>=0;i--){
        pistas[i].actualizar();
        if(jugador.colision(&pistas[i]) == true && pistas[i].getrecolectado()==false){
            pistas[i].setrecolectado(true);
            objetivo++;
            jugador.activarEuforia();
        }
        float dist=qSqrt(qPow(pistas[i].getposicionx()-agente.getposicionx(),2)+qPow(pistas[i].getposiciony()-agente.getposiciony(),2));
        if (distmin>dist&&pistas[i].getrecolectado()==false){
            distmin=dist;
            cercana=&pistas[i];
        }
    }
    agente.percibir(jugador.getposicionx(), jugador.getposiciony(),cercana);
    agente.actualizar();
    jugador.actualizar();
    puert.actualizar();
    jugador.setp(false);
    agente.setp(false);
    for(int i=6;i>=0;i--){
        if(jugador.colision(&piso[i])==true){
            resolverColision(jugador,piso[i]);
        }
        if(agente.colision(&piso[i])==true){
            resolverColision(agente,piso[i]);
        }
    }
    for(int i=plataformas.size()-1;i>=0;i--){
        plataformas[i].actualizar();
        if (jugador.colision(&plataformas[i]) == true) {
            resolverColision(jugador,plataformas[i]);
        }
        if (agente.colision(&plataformas[i]) == true) {
            resolverColision(agente,plataformas[i]);
        }
    }
    if(getdificultad()==2){
        for(int i=ganchos.size()-1;i>=0;i--){
            ganchos[i].actualizar();
            if(jugador.colision(&ganchos[i])==true&&jugador.getgancho()==false&&jugador.getespera()<0){
                jugador.agarre(ganchos[i].getposicionx(),ganchos[i].getposiciony());
                ganchoActual=i;
            }
        }
        if(jugador.getgancho()==true&&ganchoActual!=-1){
            jugador.setpivote(ganchos[ganchoActual].getposicionx(),ganchos[ganchoActual].getposiciony());
        }
        else{
            ganchoActual=-1;
        }
    }
    for(int i=balas.size()-1;i>=0;i--){
        if(balas[i]->getacti()==true){
            balas[i]->actualizar();
            for(int j=plataformas.size()-1;j>=0;j--){
                if(balas[i]->colision(&plataformas[j])){
                    balas[i]->setacti(false);
                }
            }
            for(int j=4;j>=0;j--){
                if(balas[i]->colision(&piso[j])){
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