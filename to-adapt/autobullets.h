#ifndef AUTOBULLETS_H
#define AUTOBULLETS_H

#include "bullets.h"

#define INC_AUTOBULLETS		31

class AutoBullets : public Bullets
{
public:
	AutoBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
