#include "minegun-bullet.h"
#include "../../jeubot2.h"

SDL_Surface* MinegunBullet::_surface = NULL;

MinegunBullet::MinegunBullet() : Bullet()
{
	_decVie = 0;
	_vitesse = VBULLET_MAX*VDIV;
}

void MinegunBullet::calculVitesse()
{
	if(_vx > -0.001 && _vy > -0.001 && _vx < 0.001 && _vy < 0.001)
	{
		_vx = 0;
		_vy = 0;
		_decVie = 102;
		_vitesse = 0;
		friendly = false;
	}
	else
	{
		_vx /= VDIV;
		_vy /= VDIV;
	}
}

void MinegunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/minegun/bullet.bmp", 255, 0, 255); // transparency color
}

void MinegunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

