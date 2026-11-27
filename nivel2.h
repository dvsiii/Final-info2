#ifndef NIVEL2_H
#define NIVEL2_H
#include "nivel.h"
#include "notas.h"
#include "watson.h"
#include <array>
class nivel2: public nivel
{
    watson jugador;
    std::array<notas,6> nota;
public:
    nivel2();
    void actualizar() override;
};

#endif // NIVEL2_H
