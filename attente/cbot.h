#ifndef CBOT_H
#define CBOT_H

#include "joueur.h"


class CCase
{
public:
	int score1;
	int score2;
};


class CBot : public Joueur
{
protected:
//	static CCase* cCarte;
	static CCase cCarte[XCMAX*YCMAX];
	static bool cCarteValide;
	int mode;
public:
	CCase& ccCarte(int xcc, int ycc);
	void scoreCase(int xcc, int ycc);
	void chemins(int xc, int yc);
	void initCCarte();
	CBot(int numShip);
	virtual void demanderAction();
};

#endif