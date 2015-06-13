/*
*	!!! Pb si on supprime un joueur !!!
*/

#include <math.h>
#include <sstream>
#include <iomanip>
#include "stupid.h"
#include "soins.h"
#include "bullets.h"
#include "jeubot2.h"
#include "outils.h"

#define GETLIFE     1
#define GETAMMO     2
#define ATTACK      3
#define ATTACK2     4
#define ALEATEMP    5

using std::stringstream;
using std::setw;

//Joueur* Stupid::_cible = NULL;

Stupid::Stupid(int numShip) :
	Joueur(numShip),
	_mode(0),
	_turnAlea(TURN_RIGHT),
	_timerAmmo(0),
	_xCible(0),
	_yCible(0)
{
		_cible = NULL;

		atourne = TURN_RIGHT;
		monAction = 0;
		decompte = 0;
}

void Stupid::setAction(int ac)
{
	//action |= ac;
	if(!decompte)
	{
		monAction = ac; // |=
		decompte = 10;
	}
}

void Stupid::changerCible()
{
	Joueur* c = _cible;
	int dmin = 10000;

	for(int i = 0; i < nbJoueurs(); i++)
	{
		Joueur* j = joueurs(i);
		if(j == this || j->mort())
			continue;

		int d = abs(j->x()-x()) + abs(j->y()-y());
		if(d < dmin)
		{
			dmin = d;
			c = j;
		}

	}

	_cible = c;
}


template<typename T> // le type de mbonus qu'on cherche
T* Stupid::findFirstCaseAmmo()
{
	int anx, any;
	dir(anx, any);

    int decXinit = anx;
    int decYinit = any;

    int xinit = xg2xc(x()+decXinit);
    int yinit = yg2yc(y()+decYinit);

    int dx = decYinit;
    int dy = -decXinit;

    int xd = 0;
    int yd = 0;

    int nb = 0;
    for(int j = 0; j < 20; j++)
    {
        int n = (3-abs(decXinit)-abs(decYinit))*j+1;
        int xd2 = xd;
        int yd2 = yd;
        for(int i=1; i < n; i++) // on commence à 1 pour éviter de reprendre le bonus sur lequel on est...
        {
            int casex = xinit+xd2;
            int casey = yinit+yd2;
            if(!caseValide(casex, casey))
                continue;
            T* bo = dynamic_cast<T*>(caseBonus(casex, casey));
            if(bo)
                if(bo->affichable()) // le bonus est actif
                {
                    _xCible = casex;
                    _yCible = casey;
                    return bo;
                    /*stringstream mot;
                    mot << nb;
                    afficherMot(xc2xg(xd2)+XMAX/2, yc2yg(yd2)+YMAX/2, mot.str());*/
                }
            xd2+=dx;
            yd2+=dy;
            nb++;
        }
        xd += signe(-dx-dy);
        yd += signe( dx-dy);
    }

    return false;
}

// cx et cy sont des coordonnées graphiques et non de case.
int Stupid::dirigerVers(int cx, int cy)
{
	double angCible = (360*atan2(cy-y(),cx-x())) / (2*3.141592654);
	//int da = ((int)angCible-angle()+180*3)%360;
	int da = ((((int)angCible+180*3)%360 - (angle()+180*3)%360)+180*3)%360;

    int act = 0;

    int d = abs(cx-x()) + abs(cx-y());
    //if(d > 300)
        act |= FORWARD;

    if(da > 180+25)
        act |= TURN_RIGHT; // on se rapproche grossierement de la cible
    else if(da < 180-25)
        act |= TURN_LEFT;
    else if(d < 1000) // etre assez pres pour tirer*/
    {
        tourner(da-180);	// on affine la visée
        //action |= FIRE1;
        //action |= STRAFE_LEFT;
    }

    return act;
}

void Stupid::demanderAction()
{

	action = 0;

	int xc = xg2xc(x());
	int yc = yg2yc(y());

	int anx, any;
	dir(anx, any);

	int xd, yd;
	caseVisee(xd, yd);
	bool cMD = caseMur(xd, yd) || (abs(vx()) < 0.01 && abs(vy()) < 0.01);

	if(_cible == NULL || rand() % 100 > 95)
		changerCible();

	//int vit = vx()*vx()+vy()*vy();

	if(munitions(-1) == 0)
		armeSuivante();

	if(decompte) // on va pas changer d'attitude a chaque frame hein !
	{
		decompte--;
		//if(!cMD)
		//	decompte = 0;
		if(monAction & TURN_LEFT)
			action |= TURN_LEFT;
		else if(monAction & TURN_RIGHT)
			action |= TURN_RIGHT;

		action |= FORWARD;

	}

    if(jCourant())
    {
        double angCible = (360*atan2(yc2yg(_yCible)-y(),xc2xg(_xCible)-x())) / (2*3.141592654);
        int da = ((((int)angCible+180*3)%360 - (angle()+180*3)%360)+180*3)%360;
        stringstream info;
        info << "mode = " << setw(2) << _mode
        << " timerAmmo = " << setw(4) << _timerAmmo
        << " _xCible = " << setw(3) << _xCible << " _yCible = " << setw(3) << _yCible
        << " _aCible =  " << setw(5) << da
        ;
        afficherMot(50, 20, info.str());


        afficherMot(xc2xg(_xCible)-x()+XMAX/2, yc2yg(_yCible)-y()+YMAX/2, "*");
    }


    if(cMD) // prioritaire
    {
        action |= FORWARD;
        if(cMD || (rand() < RAND_MAX/1000))
        {
            if(rand() < RAND_MAX/100 )
            {
                if(atourne == TURN_RIGHT)
                    atourne = TURN_LEFT;
                else
                    atourne = TURN_RIGHT;
            }
            setAction(atourne);
        }
    }
    else if(_mode == ALEATEMP)
    {
        action |= FORWARD;
        action |= _turnAlea;
        if(rand() % 100 < 10)
        {
            if(_turnAlea == TURN_LEFT)
                _turnAlea =  TURN_RIGHT;
            else
                _turnAlea = TURN_LEFT;
        }

        _timerAlea--;
        if(_timerAlea <= 0)
            _mode = _modePrev;
    }
    else if(_mode == GETLIFE)
    {
        bool chercher = false;
        Bonus* bo = caseBonus(_xCible, _yCible);
        if(bo)
            if(!bo->affichable()) // il est actif
                chercher = true;
        if(_timerAmmo <= 0)
            chercher = true;

        if(chercher)
        {
            //Bonus* boPrev = bo;
            bo = findFirstCaseAmmo<Soins>(); // changement de cible
            if(chercher)
            {
                //Bonus* boPrev = bo;
                bo = findFirstCaseAmmo<Soins>(); // changement de cible
                if(bo)
                    _timerAmmo = 100; // on a un certain temps pour attraper la cible
                //if(bo == boPrev) // NULL ou non : si on trouve rien (d'autre), on passe en mode aléatoire temporaire
                if(bo == NULL) // NULL ou non : si on trouve rien (d'autre), on passe en mode aléatoire temporaire
                {
                    _modePrev = GETLIFE;
                    _timerAlea = 100;
                    _mode = ALEATEMP;
                    _mode = ATTACK; // !
                }
            }
        }
        _timerAmmo--;

        action = dirigerVers(xc2xg(_xCible), yc2yg(_yCible));

        if(vie() > 0.75*ship()->vieInit())
            _mode = ATTACK;

        if(xc == _xCible && yc == _yCible)
            _mode = ATTACK;

        if(!bo)
        {
            action = FORWARD;
            if(rand() % 100 < 20)
                action |= TURN_LEFT;
        }
    }
    else if(_mode == GETAMMO)
    {
        bool chercher = true;
        Bonus* bo = caseBonus(_xCible, _yCible);
        if(bo)
            if(bo->affichable()) // il est actif
                chercher = false; // no a trouvé

        if(_timerAmmo <= 0)
            chercher = true; // cherchons un autre bonus, celui-là semble difficile à obtenir

        if(chercher)
        {
            //Bonus* boPrev = bo;
            bo = findFirstCaseAmmo<Bullets>(); // changement de cible
            if(bo)
                _timerAmmo = 100; // on a un certain temps pour attraper la cible
            /*if(bo == boPrev)
            {
                _timerAlea = 100;
                _modePrev = GETAMMO;
                _mode = ALEATEMP;
            }*/
        }
        _timerAmmo--;

        action = dirigerVers(xc2xg(_xCible), yc2yg(_yCible));

        if(xc == _xCible && yc == _yCible)
            _mode = ATTACK;

        if(!bo)
        {
            action = FORWARD;
            if(rand() % 100 < 20)
                action |= TURN_LEFT;
            /*else if(rand()%100 < 5)
                action |= TURN_RIGHT;*/
        }
    }
	else if(_mode == ATTACK)
    {
        changerCible();
        _mode = ATTACK2;
    }
    else //if(_mode == ATTACK2)
	{
        if(munitions(-1) == 0 || _cible == this) // cassos !
        {
            /**/_mode = GETAMMO;
            _timerAmmo = 0; // pour forcer la recherche

            /*/action |= FORWARD;
            if(cMD || (rand() < RAND_MAX/1000))
            {
                if(rand() < RAND_MAX/100 )
                {
                    if(atourne == TURN_RIGHT)
                        atourne = TURN_LEFT;
                    else
                        atourne = TURN_RIGHT;
                }
                setAction(atourne);
            }//*/
        }
        else if(!_cible->mort())
        {
            int d = abs(_cible->x()-x()) + abs(_cible->y()-y());
            if(d > 300)
                action |= FORWARD;


            if(cMD)
            {
                if(rand() < RAND_MAX/100 )
                {
                    if(atourne == TURN_RIGHT)
                        atourne = TURN_LEFT;
                    else
                        atourne = TURN_RIGHT;
                }
                setAction(atourne); // on se rapproche
            }
            else
            {
                int act = dirigerVers(_cible->x(),_cible->y());
                act = act & ~(int)FORWARD; /// ?? on enlève le forward pour faire notre propre traitement

                if(d < 1000) // etre assez pres pour tirer
                {
                    //tourner(da-180);	// on affine la visée
                    action |= FIRE1;
                    action |= STRAFE_LEFT;
                }
                action |= act;
            }

        }
        else
            changerCible();

        if(vie() < 0.5*ship()->vieInit())
        {
            Bonus* bo = caseBonus(_xCible, _yCible);
            if(bo)
                _mode = GETLIFE;
        }
	}



	// t'as pas le droit de tirer ! Nan mé !
	//action &= ~((int) (FIRE1 | FIRE2));


}

void Stupid::mourir(Joueur* tueur)
{
	//if( rand() % 10 > 4 )
		changerCible();
    _mode = ATTACK;
}
