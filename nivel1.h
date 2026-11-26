#ifndef NIVEL1_H
#define NIVEL1_H
#include "nivel.h"
#include "sherlock.h"
#include "watson.h"
#include "pista.h"
#include "plataforma.h"
#include "puerta.h"
#include "gancho.h"
#include "bala.h"
#include <vector>
#include <array>
class nivel1: public nivel
{
    std::vector<plataforma> plataformas;
    std::array<plataforma,7> piso;
    puerta puert;
    std::vector<gancho> ganchos;
    std::array<pista,6> pistas;
    std::vector<bala*> balas;
    sherlock jugador;
    watson agente;
    short int objetivo=0;
public:
    nivel1(short int dif);
    sherlock& getjugador();
    watson& getagente();
    std::array<pista,6>& getpistas();
    std::vector<gancho>& getganchos();
    std::vector<plataforma>& getplataformas();
    std::vector<bala*>& getbalas();
    puerta& getpuerta();
    void agregarbala(bala* b);
    void resolverColision(personaje& p,plataforma& bloque);
    void actualizar() override;
    ~nivel1();
};
#endif // NIVEL1_H