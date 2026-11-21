#include "plataforma.h"

plataforma::plataforma() {
    velocidad[0]=0;
    velocidad[1]=0;
    limites[0][0]=0;
    limites[0][1]=0;
    limites[1][0]=0;
    limites[1][1]=0;
}
float plataforma::getvx(){
    return velocidad[0];
}
float plataforma::getvy(){
    return velocidad[1];
}