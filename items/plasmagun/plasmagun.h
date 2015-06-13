#ifndef PLASMAGUN_H
#define PLASMAGUN_H

#include "../../arme.h"

#define CHARGE_MAX    20

class Jeu;

class Plasmagun : public Arme
{
private:
    int charge;
    static int _son1;
    static int _son2;
    static SDL_Surface* _surface;

public:
    Plasmagun();
    //virtual ~Plasmagun();
    
    virtual string name() { return "Plasmagun"; }
    
    virtual Arme* clone();
    
    virtual void fire1();
    virtual void fire2();
    virtual void noFire();
    
    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    virtual SDL_Surface* surface() { return _surface; }
};

#endif
