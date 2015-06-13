#include "@weapon@-ammo.h"
#include "../../jeubot2.h"

#define INC_AMMO 42

SDL_Surface* @Weapon@Ammo::_surface = NULL;
int @Weapon@Ammo::_weaponNumT = -1;

@Weapon@Ammo::@Weapon@Ammo() : Ammo()
{
}

bool @Weapon@Ammo::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_AMMO, _weaponNumT);
}

Clonable* @Weapon@Ammo::clone()
{
    return new @Weapon@Ammo();
}

void @Weapon@Ammo::gameInit(Jeu* jeu)
{
    _surface = load_image("img/@weapon@/ammo.bmp", 255, 0, 255); // transparency color
}

void @Weapon@Ammo::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

