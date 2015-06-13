#ifndef CLUSTERGUN_H
#define CLUSTERGUN_H

#include "arme.h"

class ClusterGun : public Arme
{
public:
	ClusterGun();
	virtual Arme* clone();
	virtual void fire1();
	virtual void fire2();
};

#endif
