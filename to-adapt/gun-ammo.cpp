#include "gunbullets.h"


GunBullets::GunBullets()
:	Bullets()
{
	_RECTImg.x = 0;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool GunBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_GUNBULLETS, 0);
}

