#ifndef FOLOGUN_H
#define FOLOGUN_H

#include "arme.h"

class FoloGun : public Arme
{
public:
	FoloGun();
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();

};

#endif
