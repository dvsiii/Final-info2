#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "entidad.h"

class obstaculo: public entidad
{
    bool activo;
public:
    obstaculo();
    bool getactivo();
    void setactivo(bool a);
};

#endif // OBSTACULO_H
