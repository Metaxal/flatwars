#ifndef PLASMABULLETS_H
#define PLASMABULLETS_H

#include "bullets.h"

#define INC_PLASMABULLETS		26

class PlasmaBullets : public Bullets
{
public:
	PlasmaBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
