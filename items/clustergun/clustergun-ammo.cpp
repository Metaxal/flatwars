#include "clustergun-ammo.h"
#include "../../jeubot2.h"

#define INC_AMMO 5

SDL_Surface* ClustergunAmmo::_surface = NULL;
int ClustergunAmmo::_weaponNumT = -1;

ClustergunAmmo::ClustergunAmmo() : Ammo()
{
}

bool ClustergunAmmo::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* ClustergunAmmo::clone()
{
    return new ClustergunAmmo();
}

void ClustergunAmmo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/clustergun/ammo.bmp", 255, 0, 255); // transparency color
}

void ClustergunAmmo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

