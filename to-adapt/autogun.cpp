#include "autogun.h"
#include "guideball.h"
#include "autoball.h"

AutoGun::AutoGun() : Arme()
{
	_RECTImg.x = 294;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_rateInit1 = 5;
	_rateInit2 = 10;
	_munitionsMax = 200;
	_munitionsInit = 0;

	_cibleA = NULL;
	_son1 = 4;
}

Arme* AutoGun::clone()
{
	return new AutoGun();
}

void AutoGun::fire1()
{
	if(_cibleA != NULL)
		if(_cibleA->nbMorts() != _cibleNbMorts)
			_cibleA = NULL;

	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		tireBalle(new AutoBall(_cibleA));
	}
}

void AutoGun::fire2()
{
	if(decMunitions2(1))
		tireBalle(new GuideBall(this));
}


void AutoGun::setCible(Joueur* c)
{
	if(c != NULL)
	{
		if(c->mort())
		{
			_cibleNbMorts = -1;
			c = NULL;
		}
		else
			_cibleNbMorts = c->nbMorts();
	}
	else
		_cibleNbMorts = -1;

	_cibleA = c;
}
