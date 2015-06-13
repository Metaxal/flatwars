#ifndef @WEAPON@_BULLET_H
#define @WEAPON@_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;

class @Weapon@Bullet : public Bullet
{
    static SDL_Surface* _surface;
    
public:
    @Weapon@Bullet();

    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    
    virtual SDL_Surface* surface() { return _surface; }
};


#endif
