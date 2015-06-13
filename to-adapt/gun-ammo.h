#ifndef GUNBULLETS_H
#define GUNBULLETS_H

#include "bullets.h"

#define INC_GUNBULLETS		42

class GunBullets : public Bullets
{
public:
	GunBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
