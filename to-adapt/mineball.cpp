#include "mineball.h"


MineBall::MineBall() : Balle()
{
	_RECTImg.x = 45;
	_RECTImg.y = 263;
	_RECTImg.w = DXBALLE;
	_RECTImg.h = DYBALLE;

	_decVie = 0;
	_vitesse = VBALLE_MAX*VDIV;

}

void MineBall::calculVitesse()
{
	if(_vx > -0.001 && _vy > -0.001 && _vx < 0.001 && _vy < 0.001)
	{
		_vx = 0;
		_vy = 0;
		_decVie = 102;
		_vitesse = 0;
		friendly = false;
	}
	else
	{
		_vx /= VDIV;
		_vy /= VDIV;
	}
}
