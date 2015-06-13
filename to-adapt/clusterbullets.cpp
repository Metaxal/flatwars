#include "clusterbullets.h"


ClusterBullets::ClusterBullets()
:	Bullets()
{
	_RECTImg.x = 147;
	_RECTImg.y = 305;
	_RECTImg.w = DXCASE;
	_RECTImg.h = DYCASE;
}

bool ClusterBullets::bonusAgir(Joueur *j)
{
	return j->incMunitions(INC_CLUSTERBULLETS, 3);
}

