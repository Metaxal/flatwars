#ifndef JOUEUR_H
#define JOUEUR_H

#include <vector>
#include <string>

#include "vaisseau.h"
#include "bonus.h"
#include "arme.h"
#include "bullet.h"
#include "SDL/SDL.h"

using std::vector;
using std::string;

const int FORWARD       =    1 << 0;
const int BACKWARD      =    1 << 1;
const int STRAFE_LEFT   =    1 << 2;
const int STRAFE_RIGHT  =    1 << 3;
const int TURN_LEFT     =    1 << 4;
const int TURN_RIGHT    =    1 << 5;
const int FIRE1         =    1 << 6;
const int FIRE2         =    1 << 7;
// si on depasse 32, penser a changer le type de action.

#define TOUCHE_INIT         10
#define TOUCHE_MORT_INIT    100

#define TAILLE_NOM          20

class Jeu;
class Bonus;
class Arme;
class Bullet;

/*
    Les joueurs doivent etre des pointeurs car ils sont
    désalloués par le jeu !
*/
/*
*    Classe virtuelle dont vont deriver tous les types de joueurs
*/
class Joueur
{
private:
    string _nom;
    Vaisseau _ship;
    double _x;
    double _y;
    double _vx;
    double _vy;
    double _ax;
    double _ay;
    int _angle;
    int _score;
    int _nbMorts;
    int _touche;
    bool _mort;
    bool _bRevivre;
    int _vie;
    bool _jCourant; // est-on le joueur actuel sélectionné ?
    Jeu* _zeJeu;
protected:
    int _numT;         // numero unique a un joueur
    int action;
    vector<Arme*> _armes;
    int _arme;

    static SDL_Surface* _SVieCadre;
    static SDL_Surface* _SVie;
    static int _sonMort;

public:
    Joueur(int numShip);
    void setZeJeu(Jeu* zJ) { _zeJeu = zJ; }
    Jeu* zeJeu() { return _zeJeu; }
    void init();
    void ajouterArmes(vector<Arme*> arms);
    void ajouterArme(Arme* arm);
    void armeSuivante();
    void armePrecedente();
    void tourner(int da);
    int image();
    SDL_Rect RECTImg();
    //SDL_Rect RECTImg_arme();

    static void loadSons();
    static void loadSurfaces();
    static void freeSurfaces();

    bool jCourant() { return _jCourant; }
    void setJCourant(bool j) { _jCourant = j; }

    //pseudo interface avec zeJeu
    int nbJoueurs();
    Joueur* joueurs(int i);
    Joueur* joueurCourant();
    int nbCasesX();
    int nbCasesY();
    int xEcran();
    int yEcran();
    const char* nom() { return _nom.c_str(); }
    void setNom(const char* nom);
    int x() { return (int)_x; }
    int y() { return (int)_y; }
    double vx() { return _vx; }
    double vy() { return _vy; }
    int angle() { return _angle; }
    int vie() { return _vie; }
    void incScore() { _score++; }
    void decScore() { _score--; }
    int score() const { return _score; }
    int nbMorts() const { return _nbMorts; }
    Vaisseau* ship() { return &_ship; }
    void setPos(int xg, int yg) { _x = xg; _y = yg; }
    void setNumT(int n) { _numT = n; }
    int numT() { return _numT; }
    bool touche() { return _touche > 0; }
    void decTouche() { _touche--; }
    bool toucher(int pv);
    bool incVie(int pv);
    bool incMunitions(unsigned int m, unsigned int num);
    unsigned int munitions(unsigned int num);
    virtual void demanderAction() = 0;
    bool collisionMur();
    bool collisionJoueur(Joueur* j);
    bool collision();
    bool mort() { return _mort; }
    bool revivable() { return _mort && (_touche == 0); }
    bool bRevivre() { return _bRevivre; }
    void arriver();
    void partir();
    void bouge();
    virtual void revivre() =0;
    virtual void mourir(Joueur* tueur) {}
    void purgatoire();
    void agir();
    void tireBullet(Bullet* bal, int dangle, int dxg, int dyg);
    void tireBulletAbs(Bullet* bal, int angle, int xg, int yg);
    void recul(double rec, int angle);
    void prendreBonus(Bonus* bon);
    void testerBonus();
    void dir(int& dx, int& dy);
    bool caseValide(int xc, int yc);
    void caseVisee(int& xc, int& yc);
    bool caseMur(int xc, int yc);
    Bonus* caseBonus(int xc, int yc);
    bool occupe(int xc, int yc);
    virtual ~Joueur();
    int distAvantOccupe(double dx, double dy); // mettre une limite en nombre de cases ?
    int distAugAvantOccupe(double dx, double dy);
    int distJoueurCourant();
    void jouerSonJoueur(int s);

    void afficherHUD(SDL_Surface* SScreen); // Head-Up Display
    virtual void OSD() {} // on screen display

};

#endif
