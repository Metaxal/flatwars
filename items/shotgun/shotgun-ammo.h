#ifndef SHOTGUN_AMMO_H
#define SHOTGUN_AMMO_H

#include "../../ammo.h"

class ShotgunAmmo : public Ammo
{
    static SDL_Surface* _surface;
    static int _weaponNumT;
public:

    ShotgunAmmo();

    virtual string name() { return "ShotgunAmmo"; }


    virtual void setWeaponNumT(int n) { _weaponNumT = n; }
    virtual int weaponNumT() { return _weaponNumT; }
    virtual bool bonusAgir(Joueur *j);
    
    virtual Clonable* clone();

    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    virtual SDL_Surface* surface() { return _surface; }

    // Probability of occurrence on the map, w.r.t. its size, over 10000.
    virtual unsigned int probaOcc() { return 17; }
};

#endif
