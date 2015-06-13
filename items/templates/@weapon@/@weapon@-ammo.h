#ifndef @WEAPON@_AMMO_H
#define @WEAPON@_AMMO_H

#include "../../ammo.h"

class @Weapon@Ammo : public Ammo
{
    static SDL_Surface* _surface;
    static int _weaponNumT;
public:
    @Weapon@Ammo();
	
	virtual string name() { return "@Weapon@Ammo"; }

    virtual void setWeaponNumT(int n) { _weaponNumT = n; }
    virtual int weaponNumT() { return _weaponNumT; }
	virtual bool bonusAgir(Joueur *j);
	
	virtual Clonable* clone();

	static void gameInit(Jeu* jeu);
	static void gameEnd(Jeu* jeu);
	virtual SDL_Surface* surface() { return _surface; }

	// Probability of occurrence on the map, w.r.t. its size, over 10000.
	virtual unsigned int probaOcc() { return 100; }
};

#endif
