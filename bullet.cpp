#include "bullet.h"
#include "jeu.h"
#include "main.h" // for PI
#include <math.h>
#include <iostream>


using std::cout;
using std::endl;

/*
    12 ships
    1000 bullets
    methode 1 : tester la liste des collisions avec les vaisseaux
    a chaque instant
    methode 2 : chaque case sait quel occupant elle contient

    1) 1000*12
    2) 2*12*9cases + 1000

    Methode 3 : les cases savent seulement si elles sont occupées
    par un vaisseau, donc la bullet teste seulement si la case est
    occupée, et si oui alors rechercher le vaisseau correspondant.
*/

Bullet::Bullet() : Affichable(),
    zeJeu(NULL),
    _proprio(NULL),
    _vitesse(VBULLET_MAX),
    _angle(0),
    _decVie(BULLET_DEC_VIE),
    _timeout(false)
{
}

void Bullet::init(Jeu* zJ, Joueur* j, int dangle, int dxg, int dyg)
{
    zeJeu = zJ;
    _proprio = j;
    friendly = true;
    _angle = j->angle()+dangle;


    double ang = (_angle*2*PI)/360;
    _x = j->x() + DXSHIP/2 - DXBULLET/2 +
        (/*DXSHIP/2+*/DXBULLET/2+2+dxg)*cos(ang);
    _y = j->y() + DYSHIP/2 - DYBULLET/2 +
        (/*DYSHIP/2+*/DYBULLET/2+2+dyg)*sin(ang);

//    if(_x+DXBULLET > XGMAX || _x < 0 || _y+DYBULLET > YGMAX || _y < 0)

    _vx = _vitesse*cos(ang);
    _vy = _vitesse*sin(ang);

    j->recul(_decVie/RECUL_COEF, _angle+180);
}

/*
*    Independant d'un joueur;
*    Initialise selon des coordonnées absolues
*/
void Bullet::initAbs(Jeu* zJ, Joueur* j, int angle, int xg, int yg)
{
    zeJeu = zJ;
    _proprio = j;
    friendly = false;
    _angle = angle;


    _x = xg - DXBULLET/2 + (DXBULLET/2+2)*cos(angle);
    _y = yg - DYBULLET/2 + (DYBULLET/2+2)*sin(angle);

//    if(_x+DXBULLET > XGMAX || _x < 0 || _y+DYBULLET > YGMAX || _y < 0)

    _vx = _vitesse*cos(angle);
    _vy = _vitesse*sin(angle);

}

bool Bullet::collision()
{
    /*
        On considere que les bullets sont bien plus petites que les
        cases !
        Et qu'elles ne vont pas trop vite pour ne pas passer à travers des cases.
    */
    int xc = xg2xc((int) _x + DXBULLET/2);
    int yc = yg2yc((int) _y + DYBULLET/2);
    int xc2 = xg2xc((int) (_x+_vx) + DXBULLET/2);
    int yc2 = yg2yc((int) (_y+_vy) + DYBULLET/2);

    if(!zeJeu->caseValide(xc, yc) || !zeJeu->caseValide(xc2, yc2))
    {
        cout << "ERREUR : bullet invalide  dans Bullet::collision()" << endl;
        return true;
    }

    if(zeJeu->caseMur(xc, yc) || zeJeu->caseMur(xc2, yc2))
    {
        exploseMur(xc, yc);
        return true;
        //    =>    zeJeu->enleverBullet(numT);
    }

    if(zeJeu->occupe(xc2, yc2))
    {
        Joueur* cible = zeJeu->colBulletJoueur(this);
        if(cible == NULL ||  ((cible == _proprio) && friendly))
            return false;

        cible->recul(((double)_decVie)/RECUL_COEF, _angle);
        if(cible->toucher(_decVie))
        {
            if(cible == _proprio)
                _proprio->decScore();
            else
                _proprio->incScore();

            cible->mourir(_proprio);
        }

        // il faut le mettre ici pour savoir si le joueur vient de mourir ou non !
        exploseJoueur(cible);

        return true;
        //    =>    zeJeu->enleverBullet(numT);
    }

    //friendly = false;
    return false;
}

bool Bullet::agir()
{
    if(_timeout)
        return true;

    if(collision())
        return true;

    calculVitesse();

    _x += _vx;
    _y += _vy;

    return false;
}

/*
void Bullet::tireBulletAbs(int angle)
{
    tireBulletAbs(new Bullet(), angle);
}*/

void Bullet::tireBulletAbs(Bullet* bal, int angle)
{
    _proprio->tireBulletAbs(bal, angle, _x-(_vx*2)/_vitesse, _y-(_vy*2)/_vitesse);
}


void Bullet::toExplose()
{
    _timeout = true;
}

