#include "gun-bullet.h"
#include "../../jeubot2.h"

SDL_Surface* GunBullet::_surface = NULL;

GunBullet::GunBullet() : Bullet()
{
}

void GunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/gun/bullet.bmp", 255, 0, 255); // transparency color
}

void GunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

