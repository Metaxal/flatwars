#include "trigun.h"

TriGun::TriGun() : Arme()
{
	_RECTImg.x = 49;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_rateInit1 = 20;
	_rateInit2 = 30;
	_munitionsMax = 24;
	_munitionsInit = 0;

	_son1 = 5;
	_son2 = 5;
}

Arme* TriGun::clone()
{
	return new TriGun();
}

void TriGun::fire1()
{
	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		for(int i = 0; i < 10; i++)
			tireBullet(i-5);
	}
}

void TriGun::fire2()
{
	if(decMunitions2(2))
	{
		jouerSonArme(_son2);
		for(int i = 0; i < 20; i++)
			tireBullet(i-10);
	}
}
