#include "life-bonus.h"
#include "../../main.h"

#define INC_VIE        15

SDL_Surface* LifeBonus::_surface = NULL;

bool LifeBonus::bonusAgir(Joueur *j)
{
    return j->incVie(INC_VIE);
}

Clonable* LifeBonus::clone()
{
    return new LifeBonus();
}

void LifeBonus::gameInit(Jeu* jeu)
{
    _surface = load_image("img/life/bonus.bmp", 255, 0, 255); // transparency color
}

void LifeBonus::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

