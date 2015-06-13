#ifndef GUN_BULLET_H
#define GUN_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;

class GunBullet : public Bullet
{
    static SDL_Surface* _surface;
    
public:
	GunBullet();

	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	
	virtual SDL_Surface* surface() { return _surface; }
};


#endif
