#include "pista.h"

pista::pista() {
    recolectado=false;
    id="";
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
void pista::setrecolectado(bool estado){
    recolectado=estado;
}
void pista::actualizar(){

}