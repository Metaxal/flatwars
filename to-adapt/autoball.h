#ifndef AUTOBALL_H
#define AUTOBALL_H

#include "balle.h"

class AutoBall : public Balle
{
protected:
	Joueur* _cibleA;
	int _cibleNbMorts;
	int _vmax;
public:
	AutoBall(Joueur* c = NULL, int vmax = VBALLE_MAX);
	virtual void calculVitesse();
};

#endif
