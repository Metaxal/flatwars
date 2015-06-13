#ifndef AUTOGUN_BULLET_H
#define AUTOGUN_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;
class Joueur;

class AutogunBullet : public Bullet
{
private:
    static SDL_Surface* _surface;
    
protected:
    Joueur* _cibleA;
    int _cibleNbMorts;
    int _vmax;
    
public:
    AutogunBullet(Joueur* c = NULL, int vmax = VBULLET_MAX);
    
    virtual void calculVitesse();

    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    
    virtual SDL_Surface* surface() { return _surface; }
};


#endif
