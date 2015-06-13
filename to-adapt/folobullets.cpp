#include "folobullets.h"


FoloBullets::FoloBullets()
:	Bullets()
{
	_RECTImg.x = 98;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool FoloBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_FOLOBULLETS, 2);
}

