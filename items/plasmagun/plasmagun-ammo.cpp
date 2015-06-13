#include "plasmagun-ammo.h"
#include "../../jeubot.h"

#define INC_AMMO 26

SDL_Surface* PlasmagunAmmo::_surface = NULL;
int PlasmagunAmmo::_weaponNumT = -1;

PlasmagunAmmo::PlasmagunAmmo() : Ammo()
{
}

bool PlasmagunAmmo::bonusAgir(Joueur *j)
{
    return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* PlasmagunAmmo::clone()
{
    return new PlasmagunAmmo();
}

void PlasmagunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/plasmagun/ammo.bmp", 255, 0, 255); // transparency color
}

void PlasmagunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

