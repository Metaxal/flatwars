#include "minegun.h"
#include "minegun-bullet.h"
#include "minegun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../jeubot2.h"

int Minegun::_son1 = -1;
int Minegun::_son2 = -1;
SDL_Surface* Minegun::_surface = NULL;

Minegun::Minegun() : Arme()
{
	_rateInit1 = 20;
	_rateInit2 = 20;
	_munitionsMax = 9;
	_munitionsInit = 0;
}

Arme* Minegun::clone() 
{
    return new Minegun();
}

void Minegun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/minegun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/minegun/fire1.wav");
    _son2 = NouveauSon("snd/minegun/fire2.wav");
}

void Minegun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Minegun::fire1()
{
	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		tireBullet(new MinegunBullet());
	}
}

void Minegun::fire2()
{
	if(decMunitions2(1))
	{
		jouerSonArme(_son2);
		tireBullet(new MinegunBullet(), 180);
	}
}

