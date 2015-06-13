/*
*	On pourrait faire en sorte que le joueur ne voit pas ce qui doit lui etre caché ?
*	Les murs ne sont pas transparents !
*/

#ifndef JEU_H
#define JEU_H

// #include <SDL.h>
#include "SDL/SDL.h"
#include <vector>
#include <string>
#include <map>
#include "bullet.h"
#include "bonus.h"
#include "joueur.h"
#include "arme.h"

using std::vector;
using std::string;
using std::map;
/*
	Faire un .h des constantes et y inclure "perso.h" pour les
	mods futurs ? (comment je vois pas loin encore !)
*/

extern int XMAX;
extern int YMAX;

#define DXCASE	48
#define DYCASE	48
#define XCMAX	500		// nb cases maxi en largeur
#define YCMAX	500		// nb cases maxi en hauteur
#define XGMAX	(XCMAX*DXCASE)
#define YGMAX	(YCMAX*DYCASE)

#define NB_IMG_EXPL	6

#define NB_MAX_JOUEURS	64
#define NB_MAX_BULLETS	4096

#define NB_MAX_BONUS	4000

#define OCCUPE			1 << 15 // bit uniquement utilisé pour ca !
#define VIDE			0
#define MUR				1
#define VIDE_BONUS		17

class Bullet;
class Bonus;
class Ammo;
class Arme;

struct CfgPlayer
{
    string playerClass;
    unsigned int nb; // number of players of this class to create
};

class Jeu
{
protected:
	vector<Joueur*> _joueurs;
	vector<Bullet*> _bullets;
	vector<Bonus*> _bonus;
	vector<Bonus*> _bonusKinds; // One instance of each bonus
	vector<Arme*> _armes;

	//int _nbBotsACreer;
	vector<CfgPlayer> _cfgPlayers;


	string _szFloor;

	unsigned int _jCourant;
	int _nbCasesX;
	int _nbCasesY;
	int carte[XCMAX][YCMAX];

    int _xEcran; // déclarées dans jeubot.h
    int _yEcran;


	int _scoreMode;

	SDL_Rect RECTSol, RECTViseur, RECTExpl[NB_IMG_EXPL];

public:
	Jeu();
    virtual ~Jeu();

    string szFloor() { return _szFloor; }

	int nbJoueurs() { return _joueurs.size(); }
	int nbCasesX() { return _nbCasesX; }
	int nbCasesY() { return _nbCasesY; }
	int xEcran() { return _xEcran; }
	int yEcran() { return _yEcran; }
	int carteAffWidth() { return _nbCasesX*DXCASE; }
	int carteAffHeight() { return _nbCasesY*DYCASE; }
	bool scoreMode() { return _scoreMode; }
	void scoresOn() { _scoreMode = true; }
	void scoresOff() { _scoreMode = false; }
	Joueur* joueurCourant() { return _joueurs[_jCourant]; }
	Joueur* joueurs(unsigned int i);
	bool positJoueur(Joueur* j);
	void ajouterJoueur(Joueur* j);
	void enleverJoueur(unsigned int j);
	void ajouterBullet(Bullet* bal);
	void enleverBullet(unsigned int b);
	void registerArme(Arme* arm, Ammo* ammo);
	//void enleverArme(int b); // no need to implement
	void registerBonus(Bonus* bon);
	void ajouterBonus(Bonus* bon, int xc, int yc);
	void enleverBonus(unsigned int b);
	void jCourantSuivant();
    void jMeilleurCourant();
	void jCourantLast();
	void loadBoardCfg(const string fich);
	void murs(int nb);
	void init(const string boardFile);
	void jouer();
	void afficherScores();
	void creerCarte();
	void afficherCarte(SDL_Surface* SScreen);
	void afficherCarteTxt();
	void afficherJoueurs(int xEcran, int yEcran);
	void afficherBullets(SDL_Surface* SScreen, int xEcran, int yEcran);
	Joueur* colBulletJoueur(Bullet* bal);
	bool collisionsJoueur(Joueur* j);
	bool caseValide(int xc, int yc);
	int caseMur(int xc, int yc);
	bool caseVide(int xc, int yc);
	Bonus* caseBonus(int xc, int yc);
	bool occupe(int xc, int yc);
	void arriver(int xc, int yc);
	void partir(int xc, int yc);

    Joueur* joueurPlusProche(int xg, int yg, Joueur* saufJoueur = NULL);

};

int xc2xg(int xc);
int yc2yg(int yc);
int xg2xc(int xg);
int yg2yc(int yg);
int xg2xc(double xg);
int yg2yc(double yg);

bool rectCollision(int xa1, int ya1, int xa2, int ya2, int xb1, int yb1, int xb2, int yb2);

#endif
