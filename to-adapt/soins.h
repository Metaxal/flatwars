#ifndef SOINS_H
#define SOINS_H

#include "bonus.h"

#define INC_VIE		15

class Soins : public Bonus
{
public:
	Soins();
	virtual bool bonusAgir(Joueur *j);
};

#endif
