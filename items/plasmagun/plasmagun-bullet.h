#ifndef PLASMAGUN_BULLET_H
#define PLASMAGUN_BULLET_H

#include "../autogun/autogun-bullet.h"

#include "SDL/SDL.h"

class Jeu;

class PlasmagunBullet : public AutogunBullet
{
    static SDL_Surface* _surface;
    
public:
    PlasmagunBullet(Joueur* c = NULL, int charge = 1);

    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    
    virtual SDL_Surface* surface() { return _surface; }
    //virtual void afficher(SDL_Surface* SScreen, int xg, int yg);
};


#endif
