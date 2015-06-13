#ifndef GUIDEBALL_H
#define GUIDEBALL_H

#include "balle.h"
#include "autogun.h"

class AutoGun;

/*
	Arme totalement dédié a l'autogun, et pas utilisable par d'autres !
*/
class GuideBall : public Balle
{
private:
	AutoGun* _arme;
public:
	GuideBall(AutoGun* aG);
	virtual void exploseJoueur(Joueur* cible);
	virtual void exploseMur(int xc, int yc);
};

#endif
