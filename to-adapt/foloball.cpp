#include "foloball.h"


FoloBall::FoloBall() : Balle()
{
	_RECTImg.x = 27;
	_RECTImg.y = 263;
	_RECTImg.w = DXBALLE;
	_RECTImg.h = DYBALLE;

	_decVie = 30;
	_vitesse = VBALLE_MAX*4;


}

void FoloBall::calculVitesse()
{

	int y1 = _proprio->y()-_y;
	int x1 = _proprio->x()-_x;
	int xy = x1*x1+y1*y1;

	_vx = (y1*_vitesse)/xy + _proprio->vx();
	_vy = (-x1*_vitesse)/xy + _proprio->vy();

}
