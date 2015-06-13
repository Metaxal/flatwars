#ifndef MINEGUN_H
#define MINEGUN_H

#include "arme.h"

class MineGun : public Arme
{
public:
	MineGun();
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();

};

#endif
