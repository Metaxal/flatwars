#include "shotgun-ammo.h"
#include "../../main.h"

#define INC_AMMO 5

SDL_Surface* ShotgunAmmo::_surface = NULL;
int ShotgunAmmo::_weaponNumT = -1;

ShotgunAmmo::ShotgunAmmo() : Ammo()
{
}

bool ShotgunAmmo::bonusAgir(Joueur *j)
{
    return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* ShotgunAmmo::clone()
{
    return new ShotgunAmmo();
}

void ShotgunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/shotgun/ammo.bmp", 255, 0, 255); // transparency color
}

void ShotgunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

