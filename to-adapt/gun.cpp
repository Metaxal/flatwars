#include "gun.h"
#include "foloball.h"

Gun::Gun() : Arme()
{
	_RECTImg.x = 0;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_son1 = 0;
	_son2 = 0;

	_rateInit1 = 3;
	_rateInit2 = 2;
	_munitionsMax = 117;
	_munitionsInit = 0;//53;
}

Arme* Gun::clone()
{
	return new Gun();
}

void Gun::fire1()
{

	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		tireBalle();
	}
}

void Gun::fire2()
{
	if(decMunitions2(1))
	{
		jouerSonArme(_son2);
		tireBalle(180);
	}
}
