#include "shotgun.h"
#include "shotgun-bullet.h"
#include "shotgun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../jeubot2.h"

int Shotgun::_son1 = -1;
int Shotgun::_son2 = -1;
SDL_Surface* Shotgun::_surface = NULL;

Shotgun::Shotgun() : Arme()
{
	_rateInit1 = 20;
	_rateInit2 = 30;
	_munitionsMax = 24;
	_munitionsInit = 0;
}

Arme* Shotgun::clone() 
{
    return new Shotgun();
}

void Shotgun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/shotgun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/shotgun/fire1.wav");
    _son2 = NouveauSon("snd/shotgun/fire2.wav");
}

void Shotgun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Shotgun::fire1()
{
	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		for(int i = 0; i < 10; i++)
			tireBullet(new ShotgunBullet(), i-5);
	}
}

void Shotgun::fire2()
{
	if(decMunitions2(2))
	{
		jouerSonArme(_son2);
		for(int i = 0; i < 20; i++)
			tireBullet(new ShotgunBullet(), i-10);
	}
}

