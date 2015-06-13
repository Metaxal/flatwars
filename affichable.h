#ifndef AFFICHABLE_H
#define AFFICHABLE_H

#include "SDL/SDL.h"

class Affichable
{
protected:  
    int _nImg;
    int _numImg;
    int _imgWidth;
    int _imgHeight;
    int _imgDelay;
    bool _animer;
public:
    Affichable();
    
    // This function must be redefined by the non-abstract children classes 
    // to output the surface that must be drawn to the screen
	virtual SDL_Surface* surface() =0;
	
	// Call this method in the constructor of the object to animate
	void initAnimer(int nImg, int imgWidth, int imgHeight, int imgDelay=1);
	
	virtual void afficher(SDL_Surface* SScreen, int xg, int yg);
};

#endif
