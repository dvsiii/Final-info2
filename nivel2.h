#ifndef NIVEL2_H
#define NIVEL2_H
#include "nivel.h"
#include "notas.h"
#include "watson.h"
#include <array>
#include "plataforma.h"
#include <stdexcept>
class nivel2: public nivel
{
    watson jugador;
    std::array<notas,6> nota;
    short int selecionado;
    std::array<plataforma,2> muebles;
    std::array<plataforma,4> pared;
public:
    nivel2();
    watson& getjugador();
    std::array<notas, 6>& getnotas();
    bool cercamueble(float xm, float ym);
    std::array<plataforma, 2>& getmuebles();
    short int getselecionado();
    void seleccionar(int in);
    void resolverColision(personaje& p, plataforma& bloque);
    void actualizar() override;
};

#endif // NIVEL2_H
