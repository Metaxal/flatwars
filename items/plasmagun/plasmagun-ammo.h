#ifndef PLASMAGUN_AMMO_H
#define PLASMAGUN_AMMO_H

#include "../../ammo.h"

class PlasmagunAmmo : public Ammo
{
    static SDL_Surface* _surface;
    static int _weaponNumT;
public:

    PlasmagunAmmo();

    virtual string name() { return "PlasmagunAmmo"; }


    virtual void setWeaponNumT(int n) { _weaponNumT = n; }
    virtual int weaponNumT() { return _weaponNumT; }
	virtual bool bonusAgir(Joueur *j);
	
	virtual Clonable* clone();

	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	virtual SDL_Surface* surface() { return _surface; }

	// Probability of occurrence on the map, w.r.t. its size, over 10000.
	virtual unsigned int probaOcc() { return 10; }
};

#endif
