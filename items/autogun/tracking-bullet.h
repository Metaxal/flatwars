#ifndef TRACKING_BULLET_H
#define TRACKING_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;
class Autogun;

class TrackingBullet : public Bullet
{
private:
	Autogun* _arme;

    static SDL_Surface* _surface;
    
public:
	TrackingBullet(Autogun* aG);
	
	virtual void exploseJoueur(Joueur* cible);
	virtual void exploseMur(int xc, int yc);
	
	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	
	virtual SDL_Surface* surface() { return _surface; }
};


#endif
