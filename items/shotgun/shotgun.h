#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "../../arme.h"

class Jeu;

class Shotgun : public Arme
{
    static int _son1;
    static int _son2;
    static SDL_Surface* _surface;

public:
    Shotgun();
    //virtual ~Shotgun();
    
    virtual string name() { return "Shotgun"; }
    
    virtual Arme* clone();
    
    virtual void fire1();
    virtual void fire2();
    
    // "virtual static" methods
    static void gameInit(Jeu* jeu);
    static void gameEnd(Jeu* jeu);
    virtual SDL_Surface* surface() { return _surface; }
};

#endif
