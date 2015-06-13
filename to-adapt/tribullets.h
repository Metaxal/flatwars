#ifndef TRIBULLETS_H
#define TRIBULLETS_H

#include "bullets.h"

#define INC_TRIBULLETS		5

class TriBullets : public Bullets
{
public:
	TriBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
