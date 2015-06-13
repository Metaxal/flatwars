#include "fologun.h"
#include "fologun-bullet.h"
#include "fologun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../main.h"

int Fologun::_son1 = -1;
int Fologun::_son2 = -1;
SDL_Surface* Fologun::_surface = NULL;

Fologun::Fologun() : Arme()
{
    _rateInit1 = 20;
    _rateInit2 = 20;
    _munitionsMax = 32;
    _munitionsInit = 0;
    
    initAnimer(4, 48, 48, 1);
}

Arme* Fologun::clone() 
{
    return new Fologun();
}

void Fologun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/fologun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/fologun/fire1.wav");
    _son2 = NouveauSon("snd/fologun/fire2.wav");
}

void Fologun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Fologun::fire1()
{
    if(decMunitions1(1))
    {
        jouerSonArme(_son1);
        tireBullet(new FologunBullet());
        tireBullet(new FologunBullet(), 180);
    }
}

void Fologun::fire2()
{
    if(decMunitions2(1))
    {
        jouerSonArme(_son2);
        tireBullet(new FologunBullet());
        tireBullet(new FologunBullet(), 180);
    }
}

