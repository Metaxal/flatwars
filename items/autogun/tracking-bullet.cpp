#include "tracking-bullet.h"
#include "autogun.h"
#include "../../jeubot.h"

SDL_Surface* TrackingBullet::_surface = NULL;

TrackingBullet::TrackingBullet(Autogun* aG) : Bullet()
{
	_decVie = 0;
	_vitesse = VBULLET_MAX;
	_arme = aG;
}

void TrackingBullet::exploseJoueur(Joueur* cible)
{
	_arme->setCible(cible);
}

void TrackingBullet::exploseMur(int xc, int yc)
{
	//_arme->setCible(NULL);
}

void TrackingBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/autogun/tracking-bullet.bmp", 255, 0, 255); // transparency color
}

void TrackingBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

