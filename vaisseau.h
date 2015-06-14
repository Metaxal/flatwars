#ifndef VAISSEAU_H
#define VAISSEAU_H

#include "SDL/SDL.h"

#define DXSHIP    32
#define DYSHIP    32

#define FREIN    0.1
#define ACCEL    0.3

/*
    avec V(n+1) = V(n) + acc - V(n)*frein
    => limit de la suite : V = acc/frein

  normal :
#define FREIN    0.1
#define ACCEL    0.3
  pour la glace :
#define FREIN    0.01
#define ACCEL    0.03
*/

#define BALOURD   0
#define BALEZE    1
#define MOYEN     2
#define LEGER     3
#define OISEAU    4
#define LAST_SHIP 4

#define NB_IMG_SHIP 24

class Vaisseau
{
private:
    double _acc;
    double _frein;
    int _num;
    int _vieInit;

public:
    SDL_Rect images[NB_IMG_SHIP];

public:
    double acc() { return _acc; }
    double frein() { return _frein; }
    int vieInit() { return _vieInit; }
    Vaisseau(int num);
    void initVaisseau(int num); // pour AGBot...

    int num() { return _num; }
};

#endif
