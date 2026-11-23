#include "nivel.h"

nivel::nivel() {
    dificultad=0;
    completado=false;
}
short int nivel::getdificultad(){
    return dificultad;
}
bool nivel::getcompletado(){
    return completado;
}
void nivel::setdificultad(short int nd){
    dificultad=nd;
}
void nivel::setcompletado(bool estado){
    completado=estado;
}
nivel::~nivel(){
}