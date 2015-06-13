#ifndef GUN_H
#define GUN_H

#include "arme.h"

class Gun : public Arme
{
public:
	Gun();
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();

};

#endif
