#ifndef MINEGUN_BULLET_H
#define MINEGUN_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

#define VDIV	1.7

class Jeu;

class MinegunBullet : public Bullet
{
    static SDL_Surface* _surface;
    
public:
	MinegunBullet();

	virtual void calculVitesse();

	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	
	virtual SDL_Surface* surface() { return _surface; }
};


#endif
