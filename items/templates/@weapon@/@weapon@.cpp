#include "@weapon@.h"
#include "@weapon@-bullet.h"
#include "@weapon@-ammo.h"
#include "../../jeu.h"
#include "../../son.h"
#include "../../main.h"

int @Weapon@::_son1 = -1;
int @Weapon@::_son2 = -1;
SDL_Surface* @Weapon@::_surface = NULL;

@Weapon@::@Weapon@() : Arme()
{
    _rateInit1 = 3;
    _rateInit2 = 2;
    _munitionsMax = 117;
    _munitionsInit = 0; // 53
}

Arme* @Weapon@::clone() 
{
    return new @Weapon@();
}

void @Weapon@::gameInit(Jeu* jeu)
{
    _surface = load_image("img/@weapon@/weapon.bmp", 255, 0, 255); // transparency color
    _son1 = NouveauSon("snd/@weapon@/fire1.wav");
    _son2 = NouveauSon("snd/@weapon@/fire2.wav");
}

void @Weapon@::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
    // sounds are freed globally
}

void @Weapon@::fire1()
{
    if(decMunitions1(1))
    {
        jouerSonArme(_son1);
        tireBullet(new @Weapon@Bullet());
    }
}

void @Weapon@::fire2()
{
    if(decMunitions2(1))
    {
        jouerSonArme(_son2);
        tireBullet(new @Weapon@Bullet(), 180);
    }
}

