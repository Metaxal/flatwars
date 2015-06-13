#include "autogun.h"
#include "autogun-bullet.h"
#include "tracking-bullet.h"
#include "autogun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../main.h"

int Autogun::_son1 = -1;
int Autogun::_son2 = -1;
SDL_Surface* Autogun::_surface = NULL;

Autogun::Autogun() : Arme()
{
    _rateInit1 = 5;
    _rateInit2 = 10;
    _munitionsMax = 200;
    _munitionsInit = 0;

    _cibleA = NULL;
}

Arme* Autogun::clone() 
{
    return new Autogun();
}

void Autogun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/autogun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/autogun/fire1.wav");
    _son2 = NouveauSon("snd/autogun/fire2.wav");
}

void Autogun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Autogun::fire1()
{
    if(_cibleA != NULL)
        if(_cibleA->nbMorts() != _cibleNbMorts)
            _cibleA = NULL;

    if(decMunitions1(1))
    {
        jouerSonArme(_son1);
        tireBullet(new AutogunBullet(_cibleA));
    }
}

void Autogun::fire2()
{
    if(decMunitions2(1))
        tireBullet(new TrackingBullet(this));
}

void Autogun::setCible(Joueur* c)
{
    if(c != NULL)
    {
        if(c->mort())
        {
            _cibleNbMorts = -1;
            c = NULL;
        }
        else
            _cibleNbMorts = c->nbMorts();
    }
    else
        _cibleNbMorts = -1;

    _cibleA = c;
}

