#include "autogun-ammo.h"
#include "../../jeubot.h"

#define INC_AMMO 31

SDL_Surface* AutogunAmmo::_surface = NULL;
int AutogunAmmo::_weaponNumT = -1;

AutogunAmmo::AutogunAmmo() : Ammo()
{
}

bool AutogunAmmo::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* AutogunAmmo::clone()
{
    return new AutogunAmmo();
}

void AutogunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/autogun/ammo.bmp", 255, 0, 255); // transparency color
}

void AutogunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

