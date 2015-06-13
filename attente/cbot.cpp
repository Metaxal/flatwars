#include "cbot.h"
#include <math.h>

#include "jeubot2.h"
#include "..\\utils\\clavier.h"
#include "..\\utils\utils.h"

//CCase *cCarte = NULL;
CCase CBot::cCarte[XCMAX*YCMAX];
bool CBot::cCarteValide = false;


CCase& CBot::ccCarte(int xcc, int ycc)
{
	return cCarte[xcc+ycc*nbCasesX()];
}

// on suppose qu'on est pas sur les bords !!!
void CBot::scoreCase(int xcc, int ycc)
{
	if(caseMur(xcc, ycc))
		return;

	int sc = ccCarte(xcc, ycc).score1 + 1; // 1 pour soi meme

	int nb = 0;
	for(int i = 0; i < 4; i++) // 888888888
	{
		int sc2 = ccCarte(xcc+dirs[0][i*2+1], ycc+dirs[1][i*2+1]).score1; 
		if(sc2 != 0)
		{
			sc += sc2;
			nb++;
		}
	}
/*	if(nb != 0)
		sc /= nb;*/
	sc /= 2;

	ccCarte(xcc, ycc).score2 += sc ;

}


// on suppose qu'on est jamais sur les murs du bord !!!
void CBot::chemins(int xc, int yc)
{
//	cliste


	CCase& cc = ccCarte(xc, yc);
	for(int l = 0; l < 8; l++) // 4 !!!! ou changer les % !!!!
	{
		CCase& c2 = ccCarte(xc+dirs[0][l], yc+dirs[1][l]);
		if(c2.score2 == 0) // case vierge mais pas un mur
		{
			c2.score1 = (l+4)%8; // chemin inverse
			c2.score2 = 1;//cc.score2; // case touchée
			chemins(xc+dirs[0][l], yc+dirs[1][l]);
		}
	}
}


void CBot::initCCarte()
{
//	cCarte = new CCase[nbCasesX()*nbCasesY()];

	int i, j;
	for(i = 1; i < nbCasesX()-1; i++) // on est sur qu'il y a des murs sur les bords
	for(j = 1; j < nbCasesY()-1; j++)
	{
		if(caseMur(i, j))
			ccCarte(i, j).score1 = 0; 
		else
			ccCarte(i, j).score1 = 100;
		ccCarte(i, j).score2 = 0; 
	}


	for(int k = 0; k < 8; k++)
	{
		for(i = 1; i < nbCasesX()-1; i++) // on est sur qu'il y a des murs sur les bords
		for(j = 1; j < nbCasesY()-1; j++)
			scoreCase(i, j);

		for(i = 1; i < nbCasesX()-1; i++) // on est sur qu'il y a des murs sur les bords
		for(j = 1; j < nbCasesY()-1; j++)
		{
			CCase& c = ccCarte(i, j);
			c.score1 = c.score2; 
			c.score2 = 0; 
		}
	}

	// recherche du point le plus caché possible
	int scoreMin = (4 << 14) - 1;
	int xcMin = xg2xc(x()+DXSHIP/2); 
	int ycMin = yg2yc(y()+DYSHIP/2);
	for(i = 1; i < nbCasesX()-1; i++)
	for(j = 1; j < nbCasesY()-1; j++)
	{
		int sc = ccCarte(i, j).score1;
		if(sc != 0 && sc < scoreMin)
		{
			scoreMin = sc;
			xcMin = i;
			ycMin = j;
		}
	}


	xcMin = 1;
	ycMin = 1;
	// recherche de comment aller se cacher
	for(i = 0; i < nbCasesX(); i++)
	for(j = 0; j < nbCasesY(); j++)
	{
		ccCarte(i, j).score1 = 0;

		if(caseMur(i, j))
			ccCarte(i, j).score2 = -1;
		else
			ccCarte(i, j).score2 = 0;
		
	}

	ccCarte(xcMin, ycMin).score1 = 0;
	ccCarte(xcMin, ycMin).score2 = 1;
	chemins(xcMin, ycMin);


	//delete[] CCase

}

CBot::CBot(int numShip) 
: 	Joueur(numShip)
{
	mode = 0;
}


void CBot::demanderAction()
{
	action = 0;


	int xc = xg2xc(x()+DXSHIP/2);
	int yc = yg2yc(y()+DYSHIP/2);
	int caseX = xc;
	int caseY = yc;
	bool content = false;


	if(!cCarteValide)
	{
		initCCarte();
		cCarteValide = true;
	}


	
	
	for(int i = 0; i < 8; i++)
	{
		int xcc = xc+dirs[0][i];
		int ycc = yc+dirs[1][i];
		int sc = ccCarte(xcc, ycc).score1;
		char mot[20];
		itoa(sc, mot, 10);
		afficherMot((dirs[0][i]+1)*DXCASE*2, (dirs[1][i]+1)*DYCASE*2, mot);
	}

	int sc1, sc2;
	sc1 = ccCarte(xc, yc).score1;
	sc2 = ccCarte(xc, yc).score2;
	caseX = xc+dirs[0][sc1];
	caseY = yc+dirs[1][sc1];


	content = (xc == 1 && yc == 1);


	int xcv, ycv;
	caseVisee(xcv, ycv);
	char mot[10];

	itoa(sc1, mot, 10);
	afficherMot(DXCASE*2, DYCASE*2, mot);
	itoa(sc2, mot, 10);
	afficherMot(DXCASE*2, DYCASE*3, mot);

	/*
	itoa(ccCarte(xc, yc).score1, mot, 10);
	afficherMot(DXCASE*2, DYCASE*2, mot);
	itoa(ccCarte(xcv, ycv).score1, mot, 10);
	afficherMot(0, DYCASE*6, mot);*/


	if(mode)
	{
		action |= FORWARD;
		action |= FIRE2;
		mode--;
	}
	else
	{
		if(content)
		{
			action |= FORWARD;
			action |= FIRE1;
//			mode = 150;
			tourner( (rand()*360)/RAND_MAX);
		}
		else if( (xcv == caseX) && (ycv == caseY))
		{
			action |= FORWARD;
		}
		else
		{
			double ang1 = atan2(ycv-yc, xcv-xc);
			double ang2 = atan2(caseY-yc, caseX-xc);
			int ang = ((int)(((ang2-ang1)*360)/(2*3.1415927)) + 360) % 360;
			//tourner(ang);
			if(ang >= 180)
				action |= TURN_LEFT;
			else if(ang < 180)
				action |= TURN_RIGHT;

		}
	}





		//Partie HUMAIN


		DIGetKeys();
		if(DIKeyPressed(DIK_RSHIFT))
			action = 0;
		if(DIKeyPressed(KFr_Z) || DIKeyPressed(DIK_UP))
			action |= FORWARD;
		if(DIKeyPressed(KFr_S) || DIKeyPressed(DIK_DOWN))
			action |= BACKWARD;
		if(DIKeyPressed(KFr_Q))
			action |= STRAFE_LEFT;
		if(DIKeyPressed(KFr_D))
			action |= STRAFE_RIGHT;
		if(DIKeyPressed(DIK_LEFT))
			action |= TURN_LEFT;
		if(DIKeyPressed(DIK_RIGHT))
			action |= TURN_RIGHT;
		if(DIKeyPressed(DIK_RCONTROL))
			action |= FIRE1;
		else if(DIKeyPressed(DIK_NUMPAD0))
			action |= FIRE2;





}