#ifndef FOLOGUN_H
#define FOLOGUN_H

#include "../../arme.h"

class Jeu;

class Fologun : public Arme
{
    static int _son1;
    static int _son2;
    static SDL_Surface* _surface;

public:
	Fologun();
	//virtual ~Fologun();
	
	virtual string name() { return "Fologun"; }
	
	virtual Arme* clone();
	
	virtual void fire1();
	virtual void fire2();
	
	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	virtual SDL_Surface* surface() { return _surface; }
};

#endif
