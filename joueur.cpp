#include <algorithm>
#include <math.h>
#include <iostream>
#include "joueur.h"
#include "jeu.h"
#include "jeubot.h"
#include "son.h"
#include "SDL/SDL.h"

using std::min;
using std::max;
using std::cout;
using std::endl;

int Joueur::_sonMort = -1;
SDL_Surface* Joueur::_SVieCadre = NULL;
SDL_Surface* Joueur::_SVie = NULL;


Joueur::Joueur(int numShip)
:    _ship(numShip),
    _x(0), _y(0),
    _angle(90),
    _score(0),
    _nbMorts(0),
    _mort(false),
    _bRevivre(false),
    _jCourant(false),
    _zeJeu(NULL)
{
    static int numJoueur = 0;
    numJoueur++;
    char nom[100];
    snprintf(nom, 100, "Zeb Hulon %d-%d", numShip, numJoueur);
    setNom(nom);
    //for(int i = 0; i < NB_MAX_ARMES; i++)
        //_armes[i] = NULL;
}

void Joueur::setNom(const char* nom)
{
    _nom = nom;
    //strncpy(_nom, nom, TAILLE_NOM);
}

Joueur::~Joueur()
{
    for(unsigned int i = 0; i < _armes.size(); i++)
        delete _armes[i];
}

void Joueur::init()
{
    if(_bRevivre)
        revivre();

    _vie = _ship.vieInit();
    //_vie = _ship.vieInit()/2; // FOR TESTS
    _bRevivre = false;
    _vx = 0;
    _vy = 0;
    _ax = 0;
    _ay = 0;
    _touche = 0;
    _mort = false;
    _arme = 0;
    action = 0;

    for(unsigned int i = 0; i < _armes.size(); i++)
        _armes[i]->init();
}

void Joueur::ajouterArmes(vector<Arme*> arms)
{
    for(unsigned int i = 0; i < arms.size(); i++)
    {
        ajouterArme((Arme*)(arms[i]->clone()));
        _armes[i]->init();
    }
}

void Joueur::ajouterArme(Arme* arm)
{
    // pas besoin de test, il est fait par zeJeu !!
    // donc en entrant ici, on est sur d'avoir de la place

    _armes.push_back(arm);
    //_armes[_armes.size()] = arm;
    arm->setProprio(this);
    arm->setNumT(_armes.size());
    //_armes.size()++;
}

void Joueur::armeSuivante()
{
    if(_mort)
        return;

    int n = _arme;
    do
    {
        _arme++;
        _arme %= _armes.size();
    }
    while(n != _arme && munitions(_arme) == 0);

}

void Joueur::armePrecedente()
{
    if(_mort)
        return;

    int n = _arme;
    do
    {
        _arme--;
        if(_arme < 0)
            _arme += _armes.size();
    }
    while(n != _arme && munitions(_arme) == 0);
}


void Joueur::tourner(int da)
{
    if(!_mort)
    {
        _angle += da;
        _angle %= 360;
    }
}

int Joueur::image()
{
    int im = (_angle*NB_IMG_SHIP)/360;
    im = (im + (NB_IMG_SHIP*5)/4)%NB_IMG_SHIP;

    return im;
}

SDL_Rect Joueur::RECTImg()
{
    return _ship.images[image()];
}

/*
SDL_Rect Joueur::RECTImg_arme()
{
    // if(_armes.size() > 0) !!!
    return _armes[_arme]->RECTImg();
}*/

int Joueur::nbJoueurs()
{
    return _zeJeu->nbJoueurs();
}

Joueur* Joueur::joueurs(int i)
{
    return _zeJeu->joueurs(i);
}

int Joueur::nbCasesX()
{
    return _zeJeu->nbCasesX();
}

int Joueur::nbCasesY()
{
    return _zeJeu->nbCasesY();
}

int Joueur::xEcran()
{
    return _zeJeu->xEcran();
}

int Joueur::yEcran()
{
    return _zeJeu->yEcran();
}

bool Joueur::collision()
{
    bool col = collisionMur(); // modifie _vx et _vy !!
    if(_zeJeu->collisionsJoueur(this)) // modifie _vx et _vy !!
    {
        //cout << "Collision Joueur" << endl;
        return true;
    }

    /*if(col)
        cout << "Collision Mur" << endl;
    else
        cout << "No collision" << endl;
    */
        
    return col;
}


bool Joueur::collisionMur()
{
    bool col = false;

    int x1 = (int) _x;
    int y1 = (int) _y;
    int x2 = (int)(_x + _vx);
    int y2 = (int)(_y + _vy);
    
    //printf("(%d %d) -> (%d %d)\n", x1, y1, x2, y2);

    int i;

    int xcmax = _zeJeu->nbCasesX(); // !!! different de XCMAX !!!
    int ycmax = _zeJeu->nbCasesY(); // !!! different de YMAX !!!



    // sinon :
    // selon les x
    for(i = max(0,xg2xc(x2)); i < min(xcmax, xg2xc(x2+DXSHIP)+1); i++)
    {
        for(int j = max(0,yg2yc(y1)); j < min(ycmax, yg2yc(y1+DYSHIP)+1); j++)
            if(_zeJeu->caseMur(i, j))
            {
                _vx = 0;
                col = true;
                break;
            }
        if(col)
            break;
    }

    //selon les y
    for(i = max(0,xg2xc(x1)); i < min(xcmax, xg2xc(x1+DXSHIP)+1); i++)
    {
        for(int j = max(0,yg2yc(y2)); j < min(ycmax, yg2yc(y2+DYSHIP)+1); j++)
            if(_zeJeu->caseMur(i, j))
            {
                _vy = 0;
                col = true;
                break;
            }
        if(col)
            break;
    }

    //en diagonale
    if(!col)
        for(i = max(0,xg2xc(x2)); i < min(xcmax, xg2xc(x2+DXSHIP)+1); i++)
        for(int j = max(0,yg2yc(y2)); j < min(ycmax, yg2yc(y2+DYSHIP)+1); j++)
            if(_zeJeu->caseMur(i, j))
            {
                _vx = 0;
                _vy = 0;
                return true;
            }


    return col;
}

bool Joueur::collisionJoueur(Joueur* j)
{
    bool col = false;

    /* A virer ?? */
    int x1 = (int) _x;
    int y1 = (int) _y;
    int x1v = (int)(_x+_vx);
    int y1v = (int)(_y+_vy);
    int x2 = (int) j->x();
    int y2 = (int) j->y();
    if(rectCollision(x1v, y1, x1v+DXSHIP, y1+DYSHIP,
        x2, y2, x2+DXSHIP, y2+DYSHIP))
    {
        _vx = 0;
        col = true;

    }

    if(rectCollision(x1, y1v, x1+DXSHIP, y1v+DYSHIP,
        x2, y2, x2+DXSHIP, y2+DYSHIP))
    {
        _vy = 0;
        col = true;

    }

    if(!col)
    /* Fin Partie a virer (?) */
        if(rectCollision(x1v, y1v, x1v+DXSHIP, y1v+DYSHIP,
            x2, y2, x2+DXSHIP, y2+DYSHIP))
        {
            _vx = 0;
            _vy = 0;
            return true;
        }

    return col;
}


/*
*    Renvoie vrai si on a coulé le joueur,
*    faux sinon (meme si touché)
*/
bool Joueur::toucher(int pv)
{
    if(_mort)
        return false;

    _vie -= pv;
    if (_vie <= 0)
    {
        jouerSonJoueur(_sonMort);
        _vie = 0;
        _mort = true;
        _nbMorts++;
        _touche = TOUCHE_MORT_INIT;
        return true;
    }
    else
        _touche = TOUCHE_INIT;

    return false;
}

/*
*    pv peut etre negatif
*/
bool Joueur::incVie(int pv)
{
    if(_mort)
        return false;

    if (_vie <= 0)
        _mort = true; //ce cas ne devrait pas exister si ?
    else if(_vie >= _ship.vieInit())
        _vie = _ship.vieInit();
    else
    {
        _vie += pv;
        if (_vie <= 0)
            _mort = true;
        else if(_vie > _ship.vieInit())
            _vie = _ship.vieInit();

        return true;
    }

    return false;
}

bool Joueur::incMunitions(unsigned int m, unsigned int num)
{
    if(num >= _armes.size())
        num = _arme;

    return _armes[num]->incMunitions(m);
}

unsigned int Joueur::munitions(unsigned int num)
{
    if(num >= _armes.size())
        num = _arme;

    return _armes[num]->munitions();
}



void Joueur::arriver()
{
    for(int i = max(0,xg2xc(_x)); i < min(_zeJeu->nbCasesX(), xg2xc(_x+DXSHIP)+1); i++)
    for(int j = max(0,yg2yc(_y)); j < min(_zeJeu->nbCasesY(), yg2yc(_y+DYSHIP)+1); j++)
        _zeJeu->arriver(i, j);
}

void Joueur::partir()
{
    for(int i = max(0,xg2xc(_x)); i < min(_zeJeu->nbCasesX(), xg2xc(_x+DXSHIP)+1); i++)
    for(int j = max(0,yg2yc(_y)); j < min(_zeJeu->nbCasesY(), yg2yc(_y+DYSHIP)+1); j++)
        _zeJeu->partir(i, j);
}

void Joueur::bouge()
{
    _ax -= _vx*_ship.frein();
    _ay -=  _vy*_ship.frein();
    _vx += _ax;
    _vy += _ay;

    _ax = 0; // on remet a 0 ici et si jamais on tire ou
    _ay = 0; // on se prend un choc, _ax et _ay changeront
}

void Joueur::purgatoire()
{
    demanderAction();

    bouge();
    collision(); // modifie _vx et _vy !!
    _x += _vx;
    _y += _vy;

    if((action != 0) && revivable())
    //if(revivable())
        _bRevivre = true;
}


void Joueur::agir()
{
    for(unsigned int i = 0; i < _armes.size(); i++)
        _armes[i]->decRate();

    demanderAction();

    int dangle = 0;
    double acc = 0;

    if(action & FORWARD)
    {
        acc = 3;
        if(action & STRAFE_LEFT)
            dangle = 315;
        else if(action & STRAFE_RIGHT)
            dangle = 45;
    }
    else if(action & BACKWARD)
    {
        acc = -1;
        if(action & STRAFE_LEFT)
            dangle = 45;
        else if(action & STRAFE_RIGHT)
            dangle = 315;
    }
    else if(action & STRAFE_LEFT)
    {
        acc = 2;
        dangle = 270;
    }
    else if(action & STRAFE_RIGHT)
    {
        acc = 2;
        dangle = 90;
    }

    if(action & TURN_LEFT)
        _angle += 355;
    else if(action & TURN_RIGHT)
        _angle += 5;

    _angle %= 360;


    double a2 = ((_angle+dangle)*PI)/180;
    _ax += acc*_ship.acc()*cos(a2);
    _ay += acc*_ship.acc()*sin(a2);

    bouge();
    collision(); // modifie _vx et _vy !!

    //necessite les vrais _vx et _vy !!
    if(_armes.size() > 0)
    {
        if(action & FIRE1)
            _armes[_arme]->fire1();
        else if(action & FIRE2)
            _armes[_arme]->fire2();
        else
            _armes[_arme]->noFire();
    }

    _x += _vx;
    _y += _vy;

    testerBonus();

}

void Joueur::tireBullet(Bullet* bal, int dangle, int dxg, int dyg)
{
    bal->init(_zeJeu, this, dangle, dxg, dyg);
    _zeJeu->ajouterBullet(bal);
}


void Joueur::tireBulletAbs(Bullet* bal, int angle, int xg, int yg)
{
    bal->initAbs(_zeJeu, this, angle, xg, yg);
    _zeJeu->ajouterBullet(bal);
}

void Joueur::recul(double rec, int angle)
{
    double ang = (angle*2*PI)/360;
    _ax += rec*cos(ang);
    _ay += rec*sin(ang);
}

void Joueur::prendreBonus(Bonus* bon)
{
    bon->agir(this);
}

void Joueur::testerBonus()
{
    Bonus* bon;
    for(int i = max(0,xg2xc(_x)); i < min(_zeJeu->nbCasesX(), xg2xc(_x+DXSHIP)+1); i++)
    for(int j = max(0,yg2yc(_y)); j < min(_zeJeu->nbCasesY(), yg2yc(_y+DYSHIP)+1); j++)
        if((bon = _zeJeu->caseBonus(i, j)) != NULL)
            bon->agir(this);

}

void Joueur::dir(int& dx, int& dy)
{
    int a = (angle()+360)%360;

    if( a > 270+22.5 || a < 90-22.5)
        dx = 1;
    else if( a > 90+22.5 && a < 270-22.5)
        dx = -1;
    else
        dx = 0;

    if( a > 22.5 && a < 180-22.5)
        dy = 1;
    else if( a > 180+22.5 && a < 360-22.5)
        dy = -1;
    else
        dy = 0;
}


void Joueur::caseVisee(int& xc, int& yc)
{
    int anx, any;
    dir(anx, any);

    if(anx > 0)
        xc = xg2xc(_x+DXSHIP/2)+1;
    else if(anx < 0)
        xc = xg2xc(_x+DXSHIP/2)-1;
    else
        xc = xg2xc(_x+DXSHIP/2);

    if(any > 0)
        yc = yg2yc(_y+DYSHIP/2)+1;
    else if(any < 0)
        yc = yg2yc(_y+DYSHIP/2)-1;
    else
        yc = yg2yc(_y+DYSHIP/2);
}

bool Joueur::caseValide(int xc, int yc)
{
    return _zeJeu->caseValide(xc, yc);
}

bool Joueur::caseMur(int xc, int yc)
{
    return _zeJeu->caseMur(xc, yc);
}

Bonus* Joueur::caseBonus(int xc, int yc)
{
    return _zeJeu->caseBonus(xc, yc);
}

bool Joueur::occupe(int xc, int yc)
{
    return _zeJeu->occupe(xc, yc);
}

Joueur* Joueur::joueurCourant()
{
    return _zeJeu->joueurCourant();
}


int Joueur::distJoueurCourant()
{
    Joueur* jc = joueurCourant();
    // avec les carres ? Nooon...
    return abs(jc->y() - y()) + abs(jc->x() - x());
}

/*
    Devrait rendre une struct avec la distance et la nature de l'objet que l'on vise
    renvoie le nb d'iterations avant d'atteindre un mur
    Pour avoir le nb cases, il faut faire un xg2xc (ou yg2yc en supposant que ce sont les memes)
*/
int Joueur::distAvantOccupe(double dx, double dy)
{
    double xg = x();
    double yg = y();
    int xcInit = xg2xc(xg);
    int ycInit = yg2yc(yg);
    int xc = xcInit;
    int yc = ycInit;

    int nbc = 0;

    while(xc != xcInit && yc != ycInit)
    {
        xg += dx;
        xc = xg2xc(xg);
        yg += dy;
        yc = yg2yc(yg);
    }

    while(/*!occupe(xc, yc) &&*/ !caseMur(xc, yc))
    {
        //if(xc != xcInit && yc != ycInit)
        {
            nbc++;
            xcInit = xc;
            ycInit = yc;
        }
        xg += dx;
        xc = xg2xc(xg);
        yg += dy;
        yc = yg2yc(yg);
    }


    return nbc;
}

/*
    ici on aumente la distance au fur et a mesure
     pour avoir une precision bien meilleure sur le tres proche
*/
int Joueur::distAugAvantOccupe(double dx, double dy)
{
    double xg = x()+DXSHIP/2;
    double yg = y()+DYSHIP/2;
    int xcInit = xg2xc(xg);
    int ycInit = yg2yc(yg);
    int xc = xcInit;
    int yc = ycInit;

    int nbc = 0;

    while(xc != xcInit && yc != ycInit)
    {
        xg += dx;
        xc = xg2xc(xg);
        yg += dy;
        yc = yg2yc(yg);

    }

    while(/*!occupe(xc, yc) &&*/ !caseMur(xc, yc))
    {
        nbc++;

        xg += dx;
        xc = xg2xc(xg);
        yg += dy;
        yc = yg2yc(yg);

        dx *= 1.03;
        dy *= 1.03;
        if(dx > DXCASE/2)    dx = DXCASE/2;
        if(dx < -DXCASE/2)    dx = -DXCASE/2;
        if(dy > DYCASE/2)    dy = DYCASE/2;
        if(dy < -DYCASE/2)    dy = -DYCASE/2;
    }

    return nbc;
}

void Joueur::jouerSonJoueur(int s)
{
    int d = distJoueurCourant();
    int dmax = XMAX;
    if(d > dmax)
        return;
    if(d > dmax/2)
        JouerSon(s, 16);//-1000);
    else if(d > dmax/4)
        JouerSon(s, 48);//-200);
    else if(d > dmax/8)
        JouerSon(s, 64);//-100);
    else
        JouerSon(s, 128);//0);
}

void Joueur::loadSons()
{
    _sonMort = NouveauSon("snd/death.wav");
}

void Joueur::loadSurfaces() 
{
    _SVieCadre = load_image("img/vie-cadre.bmp", 0, 0, 0);
    _SVie = load_image("img/vie.bmp", 255, 0, 255);
}

void Joueur::freeSurfaces()
{
    SDL_FreeSurface(_SVieCadre);
    SDL_FreeSurface(_SVie);
}

void Joueur::afficherHUD(SDL_Surface* SScreen)
{
    int decx = 5;
    char mot[50];

    _armes[_arme]->afficher(SScreen, decx, YMAX-5-DYARME);
    snprintf(mot, 50, "%d", munitions(-1));
    afficherMot(5+DXARME+5, YMAX-5-DYARME, mot);

    decx += 2*DXARME;
    apply_surface(SScreen, decx, YMAX-5-DYCASE, _SVieCadre);

    // Should be done relatively to the actual size of the sprite!
    SDL_Rect vieJ;
    vieJ.x = 0;
    vieJ.w = DXCASE;
    vieJ.y = 0;
    vieJ.h = DYCASE;
    int nv = DYCASE - (vie()*DYCASE)/ship()->vieInit();
    vieJ.y += nv;
    apply_surface(SScreen, 5+2*DXARME, YMAX-5-DYCASE+nv, _SVie, &vieJ);
    decx += 5+DXCASE/2;
    snprintf(mot, 50, "%d", vie());
    afficherMot(decx, YMAX-5-DYARME, mot);

    decx += DXCASE*2;
    snprintf(mot, 50, "FRAGS %d", score());
    afficherMot(decx, YMAX-5-DYARME/2, mot);
}

