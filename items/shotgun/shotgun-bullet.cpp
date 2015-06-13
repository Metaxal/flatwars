#include "shotgun-bullet.h"
#include "../../main.h"

SDL_Surface* ShotgunBullet::_surface = NULL;

ShotgunBullet::ShotgunBullet() : Bullet()
{
}

void ShotgunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/shotgun/bullet.bmp", 255, 0, 255); // transparency color
}

void ShotgunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

