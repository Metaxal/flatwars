#include "soins.h"


Soins::Soins()
:	Bonus()
{
	_RECTImg.x = 0;
	_RECTImg.y = 452;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool Soins::bonusAgir(Joueur *j)
{
	return j->incVie(INC_VIE);
}

