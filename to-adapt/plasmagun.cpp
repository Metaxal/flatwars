#include "plasmagun.h"
#include "plasma.h"
#include "joueur.h"

Gatlor::Gatlor() : Arme()
{
	charge = 0;

	_RECTImg.x = 196;
	_RECTImg.y = 354;
	_RECTImg.w = DXARME;
	_RECTImg.h = DYARME;

	_rateInit1 = 20;
	_rateInit2 = 20;
	_munitionsMax = 44;
	_munitionsInit = 0;

	_son1 = 1;
	_son2 = 2;
}

Arme* Gatlor::clone()
{
	return new Gatlor();
}

void Gatlor::fire1()
{
	if(decMunitions1(1))
	{
		jouerSonArme(_son1);
		Joueur* j = _proprio->zeJeu()->joueurPlusProche(_proprio->x(), _proprio->y(), _proprio);
		tireBalle(new Plasma(j));
	}
}

void Gatlor::fire2()
{
	if(charge < CHARGE_MAX && decMunitions2(1))
	{
		jouerSonArme(_son2);
		charge++;
	}
}

void Gatlor::noFire()
{
	if(charge > 0)
	{
		jouerSonArme(_son1);
		Joueur* j = _proprio->zeJeu()->joueurPlusProche(_proprio->x(), _proprio->y(), _proprio);
		tireBalle(new Plasma(j, charge));
		charge = 0;
	}
}

