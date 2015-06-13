#include <math.h>
#include "autogun-bullet.h"
#include "../../main.h"
#include "../../joueur.h"

SDL_Surface* AutogunBullet::_surface = NULL;

AutogunBullet::AutogunBullet(Joueur* c, int vmax) : Bullet()
{
    _vmax = vmax;
    _decVie = 15;
    _cibleA = c;
    if(c != NULL)
    {
        _cibleNbMorts = c->nbMorts();
        _vitesse = 0;
    }
    else
    {
        _cibleNbMorts = -1;
        _vitesse = _vmax/3;
    }
}

void AutogunBullet::calculVitesse()
{
    // on va pas tirer sur la cible alors qu'elle vient de respawner !

    if(_cibleA != NULL)
    {
        if(_cibleA->nbMorts() != _cibleNbMorts)
            _cibleA = NULL;
        else
        {
            double ang = atan2(_cibleA->y()+DYSHIP/2-y(), _cibleA->x()+DXSHIP/2-x());
            // faire en sorte que la vitesse soit nulle au depart, puis augmente jusqu'a max
            _vitesse += 0.2-_vitesse/(_vmax*10);
            _vx = _vitesse*cos(ang);
            _vy = _vitesse*sin(ang);
        }
    }
}

void AutogunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/autogun/bullet.bmp", 255, 0, 255); // transparency color
}

void AutogunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

