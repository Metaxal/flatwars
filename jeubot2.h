#ifndef JEUBOT2_H
#define JEUBOT2_H

#include "SDL/SDL.h"
#include <string>
#include "jeu.h"
#include "joueur.h"

using std::string;

#define DXLETTRE2	8
#define DYLETTRE2	12

#define DXLETTRE	10
#define DYLETTRE	26

#define PI	3.1415926535897932384626433832795

// Useful for debugging
#define DEBUG 0
#define PRINT_HERE if(DEBUG) cout << "line " << __LINE__ << " ok in " << __FILE__ << endl;

extern bool imagePrete;

void afficherFond();
void afficherMur(int xg, int yg, int nMur);
void afficherSol(int xg, int yg);
void afficherCase(int xg, int yg, SDL_Rect* r);
void afficherCaseCarte(int xg, int yg, SDL_Rect* r);
void afficherCarte(SDL_Rect* r);
void afficherLettre(int xg, int yg, char c);
void afficherMot(int xg, int yg, const string& mot);
void afficherBarre(int xg, int yg, SDL_Rect* r);

void afficherLettre2(int xg, int yg, char c, SDL_Surface* SDest);
void afficherMot2(int xg, int yg, const string& mot);
void afficherMotScores(int xg, int yg, const string& mot);
void afficherBarre2(int xg, int yg, SDL_Rect* r);
void initFeuilleScores();
void afficherFeuilleScores();

SDL_Surface *load_image( std::string filename, Uint8 r, Uint8 g, Uint8 b);
void apply_surface(SDL_Surface* destination, int x, int y, SDL_Surface* source, SDL_Rect* clip = NULL );

#endif
