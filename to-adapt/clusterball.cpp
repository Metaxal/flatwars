#include "clusterball.h"


ClusterBall::ClusterBall() : Balle()
{
	_RECTImg.x = 36;
	_RECTImg.y = 263;
	_RECTImg.w = DXBALLE;
	_RECTImg.h = DYBALLE;

	_decVie = 21;
	_vitesse = VBALLE_MAX/4;
	_timer = 50;
}

void ClusterBall::exploseMur(int xc, int yc)
{
	for(int i = 0; i < 36; i++)
		tireBalleAbs(i*10);
}

void ClusterBall::calculVitesse()
{
	_timer--;
	if(_timer <= 0)
	{
		for(int i = 0; i < 72; i++)
			tireBalleAbs(i*5);
		toExplose();
	}
}
