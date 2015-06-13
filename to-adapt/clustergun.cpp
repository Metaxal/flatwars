#include "clustergun.h"
#include "clusterball.h"

ClusterGun::ClusterGun() : Arme()
{
	_RECTImg.x = 147;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_rateInit1 = 30;
	_rateInit2 = 30;
	_munitionsMax = 12;
	_munitionsInit = 0;
}

Arme* ClusterGun::clone()
{
	return new ClusterGun();
}

void ClusterGun::fire1()
{
	if(decMunitions1(1))
		tireBalle(new ClusterBall());
}

void ClusterGun::fire2()
{
	int m = munitions();
	if(decMunitions2(m))
		for(int i = 0; i < m; i++)
		{
			tireBalle(new ClusterBall(), (i*30)/m-15);
		}
}
