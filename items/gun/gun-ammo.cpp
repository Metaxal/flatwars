#include "gun-ammo.h"
#include "../../jeubot2.h"

#define INC_AMMO 42

SDL_Surface* GunAmmo::_surface = NULL;
int GunAmmo::_weaponNumT = -1;

GunAmmo::GunAmmo() : Ammo()
{
}

bool GunAmmo::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* GunAmmo::clone()
{
    return new GunAmmo();
}

void GunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/gun/ammo.bmp", 255, 0, 255); // transparency color
}

void GunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

