#include "fologun-bullet.h"
#include "../../main.h"

SDL_Surface* FologunBullet::_surface = NULL;

FologunBullet::FologunBullet() : Bullet()
{
    _decVie = 30;
    _vitesse = VBULLET_MAX*4;
}

void FologunBullet::calculVitesse()
{

    int y1 = _proprio->y()-_y;
    int x1 = _proprio->x()-_x;
    int xy = x1*x1+y1*y1;

    _vx = (y1*_vitesse)/xy + _proprio->vx();
    _vy = (-x1*_vitesse)/xy + _proprio->vy();

}

void FologunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/fologun/bullet.bmp", 255, 0, 255); // transparency color
}

void FologunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

