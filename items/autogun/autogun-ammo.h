#ifndef AUTOGUN_AMMO_H
#define AUTOGUN_AMMO_H

#include "../../ammo.h"

class AutogunAmmo : public Ammo
{
    static SDL_Surface* _surface;
    static int _weaponNumT;
public:

    AutogunAmmo();

    virtual string name() { return "AutogunAmmo"; }


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
