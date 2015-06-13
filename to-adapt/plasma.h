#ifndef PLASMA_H
#define PLASMA_H

#include "autoball.h"

class Plasma : public AutoBall
{
public:
	Plasma(Joueur* c = NULL, int charge = 1);
};

#endif
