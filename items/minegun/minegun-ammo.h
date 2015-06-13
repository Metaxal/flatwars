#ifndef MINEGUN_AMMO_H
#define MINEGUN_AMMO_H

#include "../../ammo.h"

class MinegunAmmo : public Ammo
{
    static SDL_Surface* _surface;
    static int _weaponNumT;
public:

    MinegunAmmo();

    virtual string name() { return "MinegunAmmo"; }


    virtual void setWeaponNumT(int n) { _weaponNumT = n; }
    virtual int weaponNumT() { return _weaponNumT; }
    virtual bool bonusAgir(Joueur *j);
    
    virtual Clonable* clone();

    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    virtual SDL_Surface* surface() { return _surface; }

    // Probability of occurrence on the map, w.r.t. its size, over 10000.
    virtual unsigned int probaOcc() { return 5; }
};

#endif
