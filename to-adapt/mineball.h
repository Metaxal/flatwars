#ifndef MINEBALL_H
#define MINEBALL_H

#include "balle.h"

#define VDIV	1.7

class MineBall : public Balle
{
public:
	MineBall();
	virtual void calculVitesse();
};

#endif
