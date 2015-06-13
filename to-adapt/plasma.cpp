#include "plasma.h"


Plasma::Plasma(Joueur* c, int charge) : AutoBall(c, VBALLE_MAX/6)
{
	_RECTImg.x = 18;
	_RECTImg.y = 263;
	_RECTImg.w = DXBALLE;
	_RECTImg.h = DYBALLE;

	_decVie = 27*charge;
	_vitesse = _vmax; // initial speed = max speed
}

