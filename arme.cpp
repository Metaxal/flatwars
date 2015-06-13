#include <math.h>
#include "arme.h"
#include "son.h"
//#include "jeubot2.h"

int Arme::_numT = -1;

Arme::Arme() :
	_rateInit1(10),
	_rate1(0),
	_rateInit2(20),
	_rate2(0),
	_munitionsInit(0),
//	_munitionsInit(10),
	_munitionsMax(15),
	_munitions(0),
	_proprio(NULL)
{
}

Arme::~Arme()
{
}

void Arme::init()
{
	_rate1 = 0;
	_rate2 = 0;
	_munitions = _munitionsInit;
}

bool Arme::incMunitions(int m)
{
	if(_munitions >= _munitionsMax)
		return false;

	_munitions += m;
	if(_munitions >= _munitionsMax)
		_munitions = _munitionsMax;

	return true;
}

/*
*	On demande si on peut tirer n munitions, et si oui alors on
*	les enleve
*/
bool Arme::decMunitions1(int n)
{
	if(n > _munitions || _rate1 != 0)
		return false;

	_munitions -= n;
	_rate1 = _rateInit1;
	_rate2 = _rateInit2;
	return true;
}

bool Arme::decMunitions2(int n)
{
	if(n > _munitions || _rate2 != 0)
		return false;

	_munitions -= n;
	_rate2 = _rateInit2;
	_rate1 = _rateInit1;
	return true;
}

void Arme::tireBullet(Bullet* bal, int dangle, int dxg, int dyg)
{
	_proprio->tireBullet(bal, dangle, dxg, dyg);
}

void Arme::jouerSonArme(int s)
{
	_proprio->jouerSonJoueur(s);
}

