#include "vaisseau.h"

Vaisseau::Vaisseau(int num)
: _num(num)
{
    initVaisseau(num);
}

void Vaisseau::initVaisseau(int num)
{
    _num = num;
	switch(num)
	{
	case BALOURD :
		_vieInit = 400;
		_acc = ACCEL*0.6;
		_frein = FREIN;
		break;
	case BALEZE :
		_vieInit = 160;
		_acc = ACCEL*0.8;
		_frein = FREIN;
		break;
	case LEGER :
		_vieInit = 100;
		_acc = ACCEL*1.2;
		_frein = FREIN;
		break;
	case OISEAU :
		_vieInit = 80;
		_acc = ACCEL*1.6;
		_frein = FREIN;
		break;
	default /*MOYEN*/:
		_vieInit = 120;
		_acc = ACCEL;
		_frein = FREIN;
	}

	for(int i = 0; i < NB_IMG_SHIP; i++)
	{
		images[i].y = 33*num;		//inclus
		images[i].h = 32;	//non inclus
		images[i].x = i*33;		//inclus
		images[i].w = 32;	//non inclus
	}

}
