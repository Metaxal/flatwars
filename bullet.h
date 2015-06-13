#ifndef BULLET_H
#define BULLET_H

#include "SDL/SDL.h"
#include "jeu.h"
#include "joueur.h"
#include "affichable.h"

#define DXBULLET	8
#define DYBULLET	8

// mettre tout ca en variables !
#define VBULLET_MAX	(DXCASE/2)
#define RECUL_COEF	10
#define BULLET_DEC_VIE 8

class Jeu;
class Joueur;

class Bullet : public Affichable
{
protected:
	Jeu* zeJeu;
	Joueur* _proprio;
	double _x;
	double _y;
	double _vx;
	double _vy;
	double _vitesse;
	int _angle;
	int _decVie;
	bool _timeout;
	int numT;
	bool friendly;

public:
	Bullet();
	void init(Jeu* zJ, Joueur* j, int dangle, int dxg, int dyg);
	void initAbs(Jeu* zJ, Joueur* j, int angle, int xg, int yg);
	int x() { return (int)_x; }
	int y() { return (int)_y; }
	void setNumT(int n) { numT = n; }
	void tireBulletAbs(Bullet* bal, int angle);
	bool collision();
	virtual void calculVitesse() {}
	bool agir();
	virtual void exploseMur(int xc, int yc) {}
	virtual void exploseJoueur(Joueur* cible) {}
	void toExplose();
	
//	virtual SDL_Surface* surface() =0;
	
//	virtual ~Bullet() {}
};

#endif
