#ifndef MINEBULLETS_H
#define MINEBULLETS_H

#include "bullets.h"

#define INC_MINEBULLETS		3

class MineBullets : public Bullets
{
public:
	MineBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
