#include "plasmabullets.h"


PlasmaBullets::PlasmaBullets()
:	Bullets()
{
	_RECTImg.x = 196;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool PlasmaBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_PLASMABULLETS, 4);
}

