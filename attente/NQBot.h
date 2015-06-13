#ifndef NQBOT_H
#define NQBOT_H

#include "joueur.h"

class NQBot : public Joueur
{
protected:
	bool _radarOn;
	int KbForward;
	int KbBackward;
	int KbStrafeLeft;
	int KbStrafeRight;
	int KbTurnLeft;
	int KbTurnRight;
	int KbFire1;
	int KbFire2;
	int KbArmeSuivante;
	int KbRadar;
	int KbScores;


public:
	NQBot(int numShip);
	void loadPlayerCfg(const char* fich);
	void loadKbCfg(const char* fich);
	void radar();
	void afficherScores();
	void afficherDists();
	virtual void demanderAction();
};

#endif
