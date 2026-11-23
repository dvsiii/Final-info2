#ifndef NOTAS_H
#define NOTAS_H
#include "entidad.h"
class notas: public entidad
{
    bool abierta;
    short int id;
public:
    notas();
    bool getabierta();
    void setabierta(bool estado);
    short int getid();
    void setid(short int nid);
    void actualizar() override;
};
#endif // NOTAS_H