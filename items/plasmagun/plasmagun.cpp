#include "plasmagun.h"
#include "plasmagun-bullet.h"
#include "plasmagun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../joueur.h"
#include "../../jeubot2.h"

int Plasmagun::_son1 = -1;
int Plasmagun::_son2 = -1;
SDL_Surface* Plasmagun::_surface = NULL;

Plasmagun::Plasmagun() : Arme()
{
	_rateInit1 = 20;
	_rateInit2 = 20;
	_munitionsMax = 44;
	_munitionsInit = 0;

	charge = 0;
	
	initAnimer(4, 48, 48, 1);
}

Arme* Plasmagun::clone() 
{
    return new Plasmagun();
}

void Plasmagun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/plasmagun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/plasmagun/fire1.wav");
    _son2 = NouveauSon("snd/plasmagun/fire2.wav");
}

void Plasmagun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Plasmagun::fire1()
{
	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		Joueur* j = _proprio->zeJeu()->joueurPlusProche(_proprio->x(), _proprio->y(), _proprio);
		tireBullet(new PlasmagunBullet(j));
	}
}

void Plasmagun::fire2()
{
	if(charge < CHARGE_MAX && decMunitions2(1))
	{
		jouerSonArme(_son2);
		charge++;
	}
}

void Plasmagun::noFire()
{
	if(charge > 0)
	{
		jouerSonArme(_son1);
		Joueur* j = _proprio->zeJeu()->joueurPlusProche(_proprio->x(), _proprio->y(), _proprio);
		tireBullet(new PlasmagunBullet(j, charge));
		charge = 0;
	}
}

