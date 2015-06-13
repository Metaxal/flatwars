#ifndef BULLETS_H
#define BULLETS_H

#include "bonus.h"

class Ammo : public Bonus
{
public:
    //Ammo();
    virtual void setWeaponNumT(int n) =0; // { printf("Error: setWeaponNumT() must be redefined by child class.\n"); }
    virtual int weaponNumT() =0; // { printf("Error: weaponNumT() must be redefined by child class.\n"); return -1; }
};

#endif
