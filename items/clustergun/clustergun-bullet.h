#ifndef CLUSTERGUN_BULLET_H
#define CLUSTERGUN_BULLET_H

#include "../../bullet.h"
#include "SDL/SDL.h"

class Jeu;

class ClustergunBullet : public Bullet
{
private:
    static SDL_Surface* _surface;
    int _timer;
    
public:
    ClustergunBullet();

    virtual void exploseMur(int xc, int yc);
    virtual void calculVitesse();

    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    
    virtual SDL_Surface* surface() { return _surface; }
};


#endif
