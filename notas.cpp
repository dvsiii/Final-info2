#include "notas.h"

notas::notas() {
    abierta=false;
    id=0;
}
bool notas::getabierta(){
    return abierta;
}
short int notas::getid(){
    return id;
}
void notas::setabierta(bool estado){
    abierta=estado;
}
void notas::setid(short int nid){
    id=nid;
}
void notas::actualizar(){

}