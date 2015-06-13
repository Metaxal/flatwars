#include "clustergun-bullet.h"
#include "../gun/gun-bullet.h"
#include "../../jeubot.h"

SDL_Surface* ClustergunBullet::_surface = NULL;

ClustergunBullet::ClustergunBullet() : Bullet()
{
	_decVie = 21;
	_vitesse = VBULLET_MAX/4;
	_timer = 50;
}

void ClustergunBullet::exploseMur(int xc, int yc)
{
	for(int i = 0; i < 36; i++)
		tireBulletAbs(new GunBullet(), i*10);
}

void ClustergunBullet::calculVitesse()
{
	_timer--;
	if(_timer <= 0)
	{
		for(int i = 0; i < 72; i++)
			tireBulletAbs(new GunBullet(), i*5);
		toExplose();
	}
}

void ClustergunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/clustergun/bullet.bmp", 255, 0, 255); // transparency color
}

void ClustergunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

