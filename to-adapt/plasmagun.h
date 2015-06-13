#ifndef GATLOR_H
#define GATLOR_H

#include "arme.h"

#define CHARGE_MAX	20

class Gatlor : public Arme
{
private:
	int charge;
public:
	Gatlor();
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();
	virtual void noFire();
};

#endif
