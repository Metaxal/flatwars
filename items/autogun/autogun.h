#ifndef AUTOGUN_H
#define AUTOGUN_H

#include "../../arme.h"

class Jeu;

class Autogun : public Arme
{
private:
    static int _son1;
    static int _son2;
    static SDL_Surface* _surface;

protected:
	Joueur* _cibleA;
	int _cibleNbMorts;

public:
	Autogun();
	//virtual ~Autogun();
	
	virtual string name() { return "Autogun"; }
	
	virtual Arme* clone();
	
	void setCible(Joueur* c);

	virtual void fire1();
	virtual void fire2();
	
	// "virtual static" methods
	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	virtual SDL_Surface* surface() { return _surface; }
};

#endif
