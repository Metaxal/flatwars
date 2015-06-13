#include "clustergun.h"
#include "clustergun-bullet.h"
#include "clustergun-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../jeubot.h"

int Clustergun::_son1 = -1;
int Clustergun::_son2 = -1;
SDL_Surface* Clustergun::_surface = NULL;

Clustergun::Clustergun() : Arme()
{
    _rateInit1 = 30;
    _rateInit2 = 30;
    _munitionsMax = 12;
    _munitionsInit = 0;
}

Arme* Clustergun::clone() 
{
    return new Clustergun();
}

void Clustergun::gameInit(Jeu* jeu)
{
    _surface = load_image("img/clustergun/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/clustergun/fire1.wav");
    _son2 = NouveauSon("snd/clustergun/fire2.wav");
}

void Clustergun::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void Clustergun::fire1()
{
    if(decMunitions1(1))
    {
        jouerSonArme(_son1);
        tireBullet(new ClustergunBullet());
    }
}

void Clustergun::fire2()
{
    int m = munitions();
    if(decMunitions2(m))
        for(int i = 0; i < m; i++)
        {
            jouerSonArme(_son2);
            tireBullet(new ClustergunBullet(), (i*30)/m-15);
        }
}

