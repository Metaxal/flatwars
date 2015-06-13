#include "tribullets.h"


TriBullets::TriBullets()
:	Bullets()
{
	_RECTImg.x = 49;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool TriBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_TRIBULLETS, 1);
}

