#ifndef LIFE_BONUS_H
#define LIFE_BONUS_H

#include "../../bonus.h"

class LifeBonus : public Bonus
{
    static SDL_Surface* _surface;
public:
    virtual string name() { return "LifeBonus"; }

	virtual bool bonusAgir(Joueur *j);
	
	virtual Clonable* clone();

	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	virtual SDL_Surface* surface() { return _surface; }
	
	virtual unsigned int probaOcc() { return 100; }
};

#endif
