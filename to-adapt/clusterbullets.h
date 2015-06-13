#ifndef CLUSTERBULLETS_H
#define CLUSTERBULLETS_H

#include "bullets.h"

#define INC_CLUSTERBULLETS		5

class ClusterBullets : public Bullets
{
public:
	ClusterBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
