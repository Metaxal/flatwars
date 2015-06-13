#include "bonus.h"

Bonus::Bonus() :
    attente(0)
{
}

void Bonus::agir(Joueur *j)
{
    if(attente == 0)
        if(bonusAgir(j))
            attente = ATTENTE_INIT;
}

bool Bonus::affichable()
{
    return (attente == 0);
}
