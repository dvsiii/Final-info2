#ifndef PISTA_H
#define PISTA_H
#include "entidad.h"
#include <string>
class pista: public entidad
{
    bool recolectado;
    std::string id;
    float y;
    float tiempo;
public:
    pista();
    bool getrecolectado();
    std::string getid();
    void setpistay(float y);
    void setrecolectado(bool estado);
    void setid(std::string nid);
    void actualizar() override;
};

#endif // PISTA_H
