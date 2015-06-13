#include "plasmagun-bullet.h"
#include "../../main.h"

SDL_Surface* PlasmagunBullet::_surface = NULL;

PlasmagunBullet::PlasmagunBullet(Joueur* c, int charge) : AutogunBullet(c, VBULLET_MAX/6)
{
    _decVie = 27*charge;
    _vitesse = _vmax; // initial speed = max speed
    
    initAnimer(8, 8, 8, 1);
}

void PlasmagunBullet::gameInit(Jeu* jeu)
{
    _surface = load_image("img/plasmagun/bullet.bmp", 255, 0, 255); // transparency color
}

void PlasmagunBullet::gameEnd(Jeu* jeu)
{
    SDL_FreeSurface(_surface);
}

/*
void PlasmagunBullet::afficher(SDL_Surface* SScreen, int xg, int yg)
{
    const int nImg = 8;
    const int nDelay = 1;
    const int imgW = 8;
    SDL_Rect r;
    r.x = imgW * (_numImg / nDelay);
    r.y = 0;
    r.w = 8;
    r.h = 8;
    _numImg = (_numImg + 1) % (nImg * nDelay);
    //printf("r.x=%d\t_numImg=%d\n", r.x, _numImg);
    
    apply_surface(SScreen, xg, yg, surface(), &r);
}
*/
