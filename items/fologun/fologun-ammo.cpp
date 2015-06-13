#include "fologun-ammo.h"
#include "../../jeubot.h"

#define INC_AMMO 14

SDL_Surface* FologunAmmo::_surface = NULL;
int FologunAmmo::_weaponNumT = -1;

FologunAmmo::FologunAmmo() : Ammo()
{
}

bool FologunAmmo::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* FologunAmmo::clone()
{
    return new FologunAmmo();
}

void FologunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/fologun/ammo.bmp", 255, 0, 255); // transparency color
}

void FologunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

