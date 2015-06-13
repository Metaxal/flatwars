#include "fologun.h"
#include "foloball.h"

FoloGun::FoloGun() : Arme()
{
	_RECTImg.x = 98;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_rateInit1 = 20;
	_rateInit2 = 20;
	_munitionsMax = 32;
	_munitionsInit = 0;

	_son1 = 3;
}

Arme* FoloGun::clone()
{
	return new FoloGun();
}

void FoloGun::fire1()
{
	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		tireBalle(new FoloBall());
		tireBalle(new FoloBall(), 180);
	}
}

void FoloGun::fire2()
{
	if(decMunitions1(1))
		tireBalle(new FoloBall());
}
