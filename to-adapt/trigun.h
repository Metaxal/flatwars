#ifndef TRIGUN_H
#define TRIGUN_H

#include "arme.h"

class TriGun : public Arme
{
public:
	TriGun();
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();

};

#endif
