#include <math.h>
#include <fstream.h>
#include "nqbot.h"
#include "..\\utils\\clavier.h"
#include "..\\utils\\souris.h"
#include "..\\utils\\son.h"
#include "..\\utils\\utils.h"
#include "jeubot2.h"


NQBot::NQBot(int numShip)
:	Joueur(numShip),
	_radarOn(false)
{
	setNom("Boniface");
	KbForward = DIK_UP;
	KbBackward = DIK_DOWN;
	KbStrafeLeft = DIK_A;
	KbStrafeRight = DIK_D;
	KbTurnLeft = DIK_LEFT;
	KbTurnRight = DIK_RIGHT;
	KbFire1 = DIK_RCONTROL;;
	KbFire2 = DIK_NUMPAD0;
	KbRadar = DIK_R;
	KbScores = DIK_F1;
	KbArmeSuivante = DIK_E;


	loadPlayerCfg("cfg\\player1.cfg");
	loadKbCfg("cfg\\kb.cfg");

}

void NQBot::loadPlayerCfg(const char* fich)
{
	ifstream ifs(fich);

	char ligne[5000];
	while(!ifs.eof())
	{
		ifs.getline(ligne, 500, '\t');
		if(!strcmp(ligne, "NAME"))
		{
			ifs.getline(ligne, 500, '\"');
			ifs.getline(ligne, 500, '\"');
			setNom(ligne);
		}

		
		ifs.getline(ligne, 500);
	}
}


void NQBot::loadKbCfg(const char* fich)
{
	ifstream ifs(fich);

	char ligne[5000];
	while(!ifs.eof())
	{
		int touche = -1;
		ifs.getline(ligne, 500, '\"');
		ifs.getline(ligne, 500, '\"');
		if(strlen(ligne) == 1)
			touche = char2DIKey(ligne[0]);
		else
		{
			if(!strcmp(ligne, "uparrow"))
				touche = DIK_UP;
			else if(!strcmp(ligne, "downarrow"))
				touche = DIK_DOWN;
			else if(!strcmp(ligne, "leftarrow"))
				touche = DIK_LEFT;
			else if(!strcmp(ligne, "rightarrow"))
				touche = DIK_RIGHT;
			else if(!strcmp(ligne, "rightcontrol"))
				touche = DIK_RCONTROL;
			else if(!strcmp(ligne, "leftcontrol"))
				touche = DIK_LCONTROL;
		}


		ifs.getline(ligne, 500, '\"');
		ifs.getline(ligne, 500, '\"');


		if(!strcmp(ligne, "FORWARD"))
			KbForward = touche;
		else if(!strcmp(ligne, "BACKWARD"))
			KbBackward = touche;
		else if(!strcmp(ligne, "STRAFE_LEFT"))
			KbStrafeLeft = touche;
		else if(!strcmp(ligne, "STRAFE_RIGHT"))
			KbStrafeRight = touche;
		else if(!strcmp(ligne, "TURN_LEFT"))
			KbTurnLeft = touche;
		else if(!strcmp(ligne, "TURN_RIGHT"))
			KbTurnRight = touche;
		else if(!strcmp(ligne, "FIRE1"))
			KbFire1 = touche;
		else if(!strcmp(ligne, "FIRE2"))
			KbFire2 = touche;
		else if(!strcmp(ligne, "RADAR"))
			KbRadar = touche;
		else if(!strcmp(ligne, "NEXT_WEAPON"))
			KbArmeSuivante = touche;

		ifs.getline(ligne, 500);
	}

}

void NQBot::radar()
{
	afficherLettre(120, 120, '*');

	int xgmax = xc2xg(nbCasesX());
	int ygmax = yc2yg(nbCasesY());

	for(int i = 0; i < nbJoueurs(); i++)
	{
		Joueur* j = joueurs(i);
		int dx = abs(x()-j->x());
		int dy = abs(y()-j->y());

		if(dx + dy < 4000 && j != this) // 20 cases a la ronde
		{
			double ang = atan2(j->y()-y(), j->x()-x());

			afficherLettre(120 + ((100*dx)/4000)*cos(ang), 120 + ((100*dy)/4000)*sin(ang), '\'');
		}
	}

}

void NQBot::afficherScores()
{
	char mot[50];

	RECT r;

	r.top = 69;
	r.left = 1;
	r.bottom = r.top + 13;
	r.right = r.left + 270;

	afficherBarre2(XMAX/2-160, 0, r);

	afficherMot2(XMAX/2-15, 1, "Frags Deaths");


	for(int i = 0; i < nbJoueurs(); i++)
	{
		int yg = i*15+20;
		Joueur* j = joueurs(i);

		if(j == this)
		{
			r.top = 40;
			r.left = 1;
			r.bottom = r.top + 13;
			r.right = r.left + 270;
			afficherBarre2(XMAX/2-160, yg-1, r);
		}

		afficherMot2(XMAX/2-140, yg, j->nom());

		itoa(j->score(), mot, 10);
		afficherMot2(XMAX/2, yg, mot);
		
		itoa(j->nbMorts(), mot, 10);
		afficherMot2(XMAX/2+50, yg, mot);

	}
}

void NQBot::afficherDists()
{
	char mot[50];

	RECT r;

	r.top = 69;
	r.left = 1;
	r.bottom = r.top + 5;
	r.right = r.left + 270;

	for(double i = -90; i < 90; )
	{
		double dx = cos( ((angle()+i)*PI)/180 )*10;//*48;
		double dy = sin( ((angle()+i)*PI)/180 )*10;//*48;

		int nbc = distAugAvantOccupe(dx, dy); 
		if(nbc > 500) nbc = 500;

		itoa(nbc, mot, 10);
		afficherMot2(10, ((i+180)/10)*16, mot);
		r.right = r.left + nbc +2; // 250/nbc +2
		afficherBarre(30, ((i+180)/10)*16, r);

		if(i>-40 && i<40) i+= 5; else i+=20;
	}
}




void NQBot::demanderAction()
{
	if(_radarOn)
		radar();

	afficherDists();


		char mot[50];
		itoa(sqrt(vx()*vx()+vy()*vy())*10, mot, 10);
		afficherMot2(XMAX-50, 50, mot);

	action = 0;

	bool bg, bd;
	int sx, sy, sz;

	sourisGetXY(sx, sy, sz, bg, bd);
	tourner(sx);
	if(sz < 0)
		armeSuivante();
	else if(sz > 0)
		armePrecedente();

	if(bg)
		action |= FIRE1;
	if(bd)
		action |= FIRE2;

	DIGetKeys();
	if(DIKeyPressed(KbForward))
		action |= FORWARD;
	if(DIKeyPressed(KbBackward))
		action |= BACKWARD;
	if(DIKeyPressed(KbStrafeLeft))
		action |= STRAFE_LEFT;
	if(DIKeyPressed(KbStrafeRight))
		action |= STRAFE_RIGHT;
	if(DIKeyPressed(KbTurnLeft))
		action |= TURN_LEFT;
	if(DIKeyPressed(KbTurnRight))
		action |= TURN_RIGHT;
	if(DIKeyPressed(KbFire1))
		action |= FIRE1;
	else if(DIKeyPressed(KbFire2))
		action |= FIRE2;

	static aS = true;
	if(DIKeyPressed(KbArmeSuivante))
	{
		if(aS)
			armeSuivante();
		aS = false;
	}
	else
		aS = true;

	static bool rd = false;
	if(DIKeyPressed(KbRadar))
	{
		if(rd)
			_radarOn = !_radarOn;
		rd = false;
	}
	else
		rd = true;


	static bool sc = false;
	if(DIKeyPressed(KbScores))
	{
		if(sc)
			initFeuilleScores();
		else
			afficherFeuilleScores();/**/
		sc = false;
	}
	else
		sc = true;
}

