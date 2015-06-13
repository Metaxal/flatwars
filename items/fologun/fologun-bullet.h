#ifndef FOLOGUN_BULLET_H
#define FOLOGUN_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;

class FologunBullet : public Bullet
{
    static SDL_Surface* _surface;
    
public:
    FologunBullet();

    virtual void calculVitesse();

    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    
    virtual SDL_Surface* surface() { return _surface; }
};


#endif
