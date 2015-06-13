#ifndef AUTOGUN_H
#define AUTOGUN_H

#include "arme.h"
#include "guideball.h"

class AutoGun : public Arme
{
protected:
	Joueur* _cibleA;
	int _cibleNbMorts;
public:
	AutoGun();
	void setCible(Joueur* c);
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();
};

#endif
