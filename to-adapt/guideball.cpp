#include "guideball.h"


GuideBall::GuideBall(AutoGun* aG) : Balle()
{
	_RECTImg.x = 54;
	_RECTImg.y = 263;
	_RECTImg.w = DXBALLE;
	_RECTImg.h = DYBALLE;

	_decVie = 0;
	_vitesse = VBALLE_MAX;
	_arme = aG;


}

void GuideBall::exploseJoueur(Joueur* cible)
{
	_arme->setCible(cible);
}


void GuideBall::exploseMur(int xc, int yc)
{
	//_arme->setCible(NULL);
}
