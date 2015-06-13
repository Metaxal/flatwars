#include "gun.h"
#include "gun-bullet.h"
#include "gun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../main.h"

int Gun::_son1 = -1;
int Gun::_son2 = -1;
SDL_Surface* Gun::_surface = NULL;

Gun::Gun() : Arme()
{
    _rateInit1 = 3;
    _rateInit2 = 2;
    _munitionsMax = 117;
    _munitionsInit = 0; // 53
}

Arme* Gun::clone() 
{
    return new Gun();
}

void Gun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/gun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/gun/fire1.wav");
    _son2 = NouveauSon("snd/gun/fire2.wav");
}

void Gun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Gun::fire1()
{
    if(decMunitions1(1))
    {
        jouerSonArme(_son1);
        tireBullet(new GunBullet());
    }
}

void Gun::fire2()
{
    if(decMunitions2(1))
    {
        jouerSonArme(_son2);
        tireBullet(new GunBullet(), 180);
    }
}

