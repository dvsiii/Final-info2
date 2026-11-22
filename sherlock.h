#ifndef SHERLOCK_H
#define SHERLOCK_H
#include "personaje.h"
class sherlock: public personaje
{
    bool gancho;
public:
    sherlock();
    bool getgancho();
    void setgancho(bool estado);
    void actualizar() override;
};

#endif // SHERLOCK_H
