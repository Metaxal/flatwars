#include "minebullets.h"


MineBullets::MineBullets()
:	Bullets()
{
	_RECTImg.x = 245;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool MineBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_MINEBULLETS, 5);
}

