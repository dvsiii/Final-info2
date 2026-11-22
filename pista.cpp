#include "pista.h"
#include <QtMath>
pista::pista() {
    recolectado=false;
    id="";
    y=0;
    tiempo=0;
}
bool pista::getrecolectado(){
    return recolectado;
}
std::string pista::getid(){
    return id;
}
void pista::setid(std::string nid){
    id=nid;
}
void pista::setpistay(float ny){
    y=ny;
}
void pista::setrecolectado(bool estado){
    recolectado=estado;
}
void pista::actualizar(){
    if(recolectado==false){
        sety(y+5*qSin(2*tiempo));
        tiempo+=0.016f;
    }
}