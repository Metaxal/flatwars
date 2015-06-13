#include "minegun.h"
#include "mineball.h"

MineGun::MineGun() : Arme()
{
	_RECTImg.x = 245;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_rateInit1 = 20;
	_rateInit2 = 5;
	_munitionsMax = 9;
	_munitionsInit = 0;
}

Arme* MineGun::clone()
{
	return new MineGun();
}

void MineGun::fire1()
{
	if(decMunitions1(1))
		tireBalle(new MineBall());
}

void MineGun::fire2()
{
	//explose all ?
	if(decMunitions2(1))
		tireBalle(new MineBall());
}
