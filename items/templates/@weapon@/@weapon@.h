#ifndef @WEAPON@_H
#define @WEAPON@_H

#include "../../arme.h"

class Jeu;

class @Weapon@ : public Arme
{
    static int _son1;
    static int _son2;
    static SDL_Surface* _surface;

public:
	@Weapon@();
	//virtual ~@Weapon@();
	
	virtual string name() { return "@Weapon@"; }
	
	virtual Arme* clone();
	
	virtual void fire1();
	virtual void fire2();
	
	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	virtual SDL_Surface* surface() { return _surface; }
};

#endif
