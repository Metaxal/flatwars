#include "minegun-ammo.h"
#include "../../jeubot.h"

#define INC_AMMO 3

SDL_Surface* MinegunAmmo::_surface = NULL;
int MinegunAmmo::_weaponNumT = -1;

MinegunAmmo::MinegunAmmo() : Ammo()
{
}

bool MinegunAmmo::bonusAgir(Joueur *j)
{
    return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* MinegunAmmo::clone()
{
    return new MinegunAmmo();
}

void MinegunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/minegun/ammo.bmp", 255, 0, 255); // transparency color
}

void MinegunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

