#include "affichable.h"
#include "jeubot.h"

Affichable::Affichable() :
    _animer(false)
{
}

void Affichable::initAnimer(int nImg, int imgWidth, int imgHeight, int imgDelay)
{
    _nImg = nImg;
    _imgWidth = imgWidth;
    _imgHeight = imgHeight;
    _imgDelay = imgDelay;
    _numImg = 0;
    _animer = true;
}

void Affichable::afficher(SDL_Surface* SScreen, int xg, int yg)
{
    if(_animer) 
    {
        SDL_Rect r;
        r.x = _imgWidth * (_numImg / _imgDelay);
        r.y = 0;
        r.w = _imgWidth;
        r.h = _imgHeight;
        _numImg = (_numImg + 1) % (_nImg * _imgDelay);
        //printf("r.x=%d\t_numImg=%d\n", r.x, _numImg);
        
	    apply_surface(SScreen, xg, yg, surface(), &r);
    } 
    else
    {
    	apply_surface(SScreen, xg, yg, surface());
	}
}

