#ifndef SHOTGUN_BULLET_H
#define SHOTGUN_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;

class ShotgunBullet : public Bullet
{
    static SDL_Surface* _surface;
    
public:
	ShotgunBullet();

	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	
	virtual SDL_Surface* surface() { return _surface; }
};


#endif
