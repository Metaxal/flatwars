#ifndef HUMAIN_H
#define HUMAIN_H

#include "../../joueur.h"

class Humain : public Joueur
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
	Humain(int numShip);
	void loadPlayerCfg(const char* fich);
	void loadKbCfg(const char* fich);
	void radar();
	//void afficherScores();
	void afficherDists();
	virtual void demanderAction();
    virtual void revivre() {}
    virtual void OSD();
};

#endif
