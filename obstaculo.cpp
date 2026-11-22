#include "obstaculo.h"

obstaculo::obstaculo() {
    activo=true;
}
bool obstaculo::getactivo(){
    return activo;
}
void obstaculo::setactivo(bool a){
    activo=a;
}