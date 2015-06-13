#include "autobullets.h"


AutoBullets::AutoBullets()
:	Bullets()
{
	_RECTImg.x = 294;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool AutoBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_AUTOBULLETS, 6);
}

