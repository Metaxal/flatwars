#include <math.h>
#include "autoball.h"


AutoBall::AutoBall(Joueur* c, int vmax) : Balle()
{
    _vmax = vmax;
	_RECTImg.x = 63;
	_RECTImg.y = 263;
	_RECTImg.w = DXBALLE;
	_RECTImg.h = DYBALLE;

	_decVie = 15;
	_cibleA = c;
	if(c != NULL)
	{
		_cibleNbMorts = c->nbMorts();
		_vitesse = 0;
	}
	else
	{
		_cibleNbMorts = -1;
		_vitesse = _vmax/3;
	}

}

void AutoBall::calculVitesse()
{
	// on va pas tirer sur la cible alors qu'elle vient de respawner !

	if(_cibleA != NULL)
	{
		if(_cibleA->nbMorts() != _cibleNbMorts)
			_cibleA = NULL;
		else
		{
			double ang = atan2(_cibleA->y()+DYSHIP/2-y(), _cibleA->x()+DXSHIP/2-x());
			// faire en sorte que la vitesse soit nulle au depart, puis augmente jusqu'a max
			_vitesse += 0.2-_vitesse/(_vmax*10);
			_vx = _vitesse*cos(ang);
			_vy = _vitesse*sin(ang);
		}
	}
}

