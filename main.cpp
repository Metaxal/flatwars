#define NAME "FlatWars"
#define TITLE "FlatWars"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "main.h"
#include "souris.h"
#include "son.h"
#include "vaisseau.h"


using std::ifstream;
using std::cout;
using std::endl;

//Screen attributes
int BPP  = 32;
int XMAX = 320;
int YMAX = 240;
int FULLSCREEN_MODE = 0;

// Max frame rate (ms)
Uint32 delayFrame = 40;
// Max play rate (ms)
Uint32 delayPlay = 30;



//The surfaces
SDL_Surface* SScreen = NULL;
SDL_Surface* SBots = NULL;
SDL_Surface* SWalls = NULL;
SDL_Surface* SFloor = NULL;
SDL_Surface* SLettres = NULL;
SDL_Surface* SLettres2 = NULL;
SDL_Surface* SCarte = NULL; // INUTILISé

//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };



Jeu* zeJeu;

bool montrerScores = false;
bool jeuPause = false;

string szGameCfg = "cfg/game.cfg";
string szBoardCfg = "cfg/board.cfg";

string szBots = "img/bots.bmp";
string szWalls = "img/walls.bmp";
//string szFloor = "img/floor.bmp";
string szLettres = "img/police1.bmp";
string szLettres2 = "img/police2.bmp";

bool imagePrete = true;
bool isAppActive = true;


void loadGameCfg(string fich)
{
    ifstream ifs(fich.c_str());

    char ligne[5000];
    while(!ifs.eof())
    {
        ifs.getline(ligne, 500, '=');
        if(!strcmp(ligne, "XMAX"))
            ifs >> XMAX;
        else if(!strcmp(ligne, "YMAX"))
            ifs >> YMAX;
        else if(!strcmp(ligne, "FULLSCREEN"))
            ifs >> FULLSCREEN_MODE;

        ifs.getline(ligne, 500);
    }

}

SDL_Surface *load_image( std::string filename, Uint8 r, Uint8 g, Uint8 b)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Color key surface
        SDL_SetColorKey( loadedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( loadedImage->format, r, g, b ) );

        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface, must be done after setting colorkey !
        SDL_FreeSurface( loadedImage );
    }

    if(optimizedImage == NULL)
    {
        cout << "Error while loading image " << filename << endl <<
            SDL_GetError() << endl;
    }

    //Return the optimized surface
    return optimizedImage;
}

// clip is optional, if NULL the entire source surface is applied to dest
// at (x, y).
void apply_surface(SDL_Surface* destination, int x, int y, SDL_Surface* source, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect r;

    //Get offsets
    r.x = x;
    r.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &r );
}

/*
*    Un sprite est un rectangle dans une image source, que l'on colle sur une image destination.
*    Si ce sprite doit etre clippé, on reduit provisoirement les dimensions de ce rectangle.
*/
bool clip(SDL_Surface* SDest, SDL_Surface* SSource, SDL_Rect* sprite, int x, int y)
{
    apply_surface(SDest, x, y, SSource, sprite);
    return true;
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to set
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

// La surface doit etre lockée !!
// VOIR file:///D:/prog/SDL-1.2.12/docs/html/guidevideo.html
void PutPix(int x, int y, int cr, int cg, int cb, SDL_Surface *Surf)
{
    Uint32 color;
    color = SDL_MapRGB(Surf->format, cr, cg, cb);
    putpixel(Surf, x, y, color);
}

// La surface doit etre lockée !!
// VOIR file:///D:/prog/SDL-1.2.12/docs/html/guidevideo.html
void GetPix(int x, int y, Uint8* cr, Uint8* cg, Uint8* cb, SDL_Surface *Surf)
{
    Uint32 color = getpixel(Surf, x, y);
    SDL_GetRGB(color, Surf->format, cr, cg, cb);
}

/*
*    Suppose que le centre de rotation est le centre du rectangle
*/
//void rotations(int x, int y, int dx, int dy, int nb, LPDIRECTDRAWSURFACE lpDDS)
void rotations(int x, int y, int dx, int dy, int nb, SDL_Surface* Surf)
{
    if ( SDL_MUSTLOCK(SBots) )
    {
        if ( SDL_LockSurface(SBots) < 0 )
    {
            std::cerr << "Can't lock screen: " << SDL_GetError() << endl;
            return;
        }
    }

    //putpixel(screen, x, y, yellow);

    double dangle = (2*PI)/nb;
    double angle = 0;

    for(int n = 1; n < nb; n++)
    {
        angle -= dangle;

        for(int i = 0; i < dx; i++)
        for(int j = 0; j < dy; j++)
        {
            // il faudrait faire une moyenne pondérée, selon la valeur apres la virgule, des pixels autour du pixel source

            double x2;
            double y2;
            if(i == dx/2 && j == dy/2)
            {
                x2 = x+dx/2+0.1;
                y2 = y+dy/2+0.1;
            }
            else
            {
                x2 = x+dx/2+(i-dx/2)*cos(angle)-(j-dy/2)*sin(angle);
                y2 = y+dy/2+(i-dx/2)*sin(angle)+(j-dy/2)*cos(angle);
            }

            if(x2 > x && x2 < x+dx && y2 > y && y2 < y+dy)
            {
                Uint32 p = getpixel(SBots, x2, y2);
                putpixel(SBots, x+n*(dx+1)+i, y+j, p);
            }
            else
                //;
                putpixel(SBots, x+n*(dx+1)+i, y+j, SBots->format->colorkey);

        }

    }

    if ( SDL_MUSTLOCK(SBots) )
        SDL_UnlockSurface(SBots);
}

void afficherMur(int xg, int yg, int nMur)
{
    SDL_Rect rm;// = RECTMur;
    rm.x = (nMur-1)*(DXCASE+1);
    rm.y = 0;
    rm.w = DXCASE;
    rm.h = DYCASE;
    clip(SScreen, SWalls, &rm, xg, yg);
}

void afficherSol(int xg, int yg)
{
    apply_surface(SScreen, xg, yg, SFloor);
}

void afficherCase(int xg, int yg, SDL_Rect* r)
{
    //clip et affiche le sprite
    //apply_surface(xg, yg, SBots, SScreen, r);
    clip(SScreen, SBots, r, xg, yg);
}

void afficherCaseCarte(int xg, int yg, SDL_Rect* r)
{
    //clip et affiche le sprite
    //apply_surface(xg, yg, SBots, SScreen, r);
    clip(SCarte, SBots, r, xg, yg);
}

void afficherCarte(SDL_Rect* r)
{
    //clip et affiche le sprite
    //apply_surface(xg, yg, SBots, SScreen, r);
    clip(SScreen, SCarte, r, 0, 0);
}

/*
Ne pas oublier l'espace au debut
 !"$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ
[\]^_`abcdefghijklmnopqrstuvwxyz{|}

*/
void afficherLettre(int xg, int yg, char c)
{
    if(c < ' ' || c > '}')
        return;

    SDL_Rect r;
    if(c <= 'Z')
    {
        r.x = DXLETTRE*(c-' ');
        r.y = 0;
    }
    else
    {
        r.x = DXLETTRE*(c-'[');
        r.y = 28;
    }
    r.w = DXLETTRE;
    r.h = DYLETTRE;

    clip(SScreen, SLettres, &r, xg, yg);
}


void afficherMot(int xg, int yg, const string& mot)
{
    for(unsigned int i = 0; i < mot.size(); i++)
        afficherLettre(xg + i*DXLETTRE, yg, mot[i]);
}

void afficherBarre(int xg, int yg, SDL_Rect* r)
{
    clip(SScreen, SLettres2, r, xg, yg);
}

void afficherLettre2(int xg, int yg, char c, SDL_Surface* SDest)
{
    if(c <= ' ' || c > '}')
        return;

    SDL_Rect r;
    if(c <= 'Z')
    {
        r.x = DXLETTRE2*(c-' ');
        r.y = 0;
    }
    else
    {
        r.x = DXLETTRE2*(c-'[');
        r.y = 15;
    }
    r.w = DXLETTRE2;
    r.h = DYLETTRE2;

    clip(SDest, SLettres2, &r, xg, yg);
}

void afficherMot2(int xg, int yg, const string& mot)
{
    for(unsigned int i = 0; i < mot.size(); i++)
        afficherLettre2(xg + i*DXLETTRE2, yg, mot[i], SScreen);
}

void afficherMotScores(int xg, int yg, const string& mot)
{
    for(unsigned int i = 0; i < mot.size(); i++)
        afficherLettre2(xg + i*DXLETTRE2, yg, mot[i], SScreen);
}


void afficherBarre2(int xg, int yg, SDL_Rect* r)
{
    clip(SScreen, SLettres2, r, xg, yg);
}

bool init()
{
    srand( time(NULL) );

    PRINT_HERE

    char msg[] = "SDL_VIDEODRIVER=x11";
    SDL_putenv(msg);

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    PRINT_HERE

    PRINT_HERE

    SScreen = SDL_SetVideoMode( XMAX, YMAX, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF | (SDL_FULLSCREEN * FULLSCREEN_MODE) );


    char namebuf[50];
    SDL_VideoDriverName(namebuf, 50);
    if(DEBUG) cout << "namebuf = " << namebuf << endl;

    //If there was an error in setting up the screen
    if( SScreen == NULL )
        return false;

    PRINT_HERE

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
        return false;

    PRINT_HERE

    if( !InitSon())
        return false;

    //Set the window caption
    SDL_WM_SetCaption( "FlatWars", NULL );

    PRINT_HERE

    initSouris(XMAX, YMAX);
    SDL_ShowCursor(SDL_DISABLE);

    PRINT_HERE

    //zeJeu = Jeu::getInstance(); // new Jeu();
    zeJeu = new Jeu();
    zeJeu->init(szBoardCfg);

    PRINT_HERE

    //If everything initialized fine
    return true;
}

bool loadSurfaces()
{
    SBots = load_image( szBots, 255, 0, 255 );
    SWalls = load_image( szWalls, 255, 0, 255 );
    SFloor = load_image( zeJeu->szFloor(), 255, 0, 255 );
    SLettres = load_image( szLettres, 255, 0, 255 );
    SLettres2 = load_image( szLettres2, 0, 0, 0 );

    if(!SBots || !SWalls || !SFloor || !SLettres || !SLettres2)
        return false;

    PRINT_HERE

    for(int i = 0; i < 5; i++)
        rotations(0, (DXSHIP+1)*i, DXSHIP, DYSHIP, NB_IMG_SHIP, SBots);

    PRINT_HERE

    Joueur::loadSons();

    PRINT_HERE

    Joueur::loadSurfaces();

    //If everything loaded fine
    return true;
}

bool load_files()
{
    PRINT_HERE

    return loadSurfaces();
}

void finSurfaces()
{
    //Free the surfaces
    SDL_FreeSurface(SBots);
    SDL_FreeSurface(SWalls);
    SDL_FreeSurface(SFloor);
    SDL_FreeSurface(SLettres);
    SDL_FreeSurface(SLettres2);
}

void clean_up()
{
    delete zeJeu;

    finSurfaces();

    finSouris();

    FinSons();

    //Close the font
    TTF_CloseFont(font);

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

void updateFrame()
{
    static Uint32 nbFrames = 0;
      static Uint32 lastNbFrames = 0;
    static Uint32 tframe1000 = 0;
    static Uint32 lastTickCountPlay = 0;
    static Uint32 lastTickCountFrame = 0;

    int tc = SDL_GetTicks();

    imagePrete = /** /nbFrames % 20 >= 19;/*/ true;/**/

    // Every ticks?
    if(!jeuPause)
        if(tc - lastTickCountPlay > delayPlay)
        {
            zeJeu->jouer();
            lastTickCountPlay = tc;
        }

    //if(imagePrete)
    if(tc - lastTickCountFrame > delayFrame)
    {
        if(!jeuPause)
        {
            if(imagePrete) {
                nbFrames++;
                zeJeu->afficherCarte(SScreen);
            }
        }
        else
        {
            afficherMot(XMAX/2, YMAX/2, "PAUSE");
            SDL_Delay(500);
        }

        if(montrerScores)
            zeJeu->afficherScores();

        /**/
        char mot[20];
        sprintf(mot, "%d fps", ((nbFrames - lastNbFrames + 1) * 1000) / (tc - tframe1000 + 1));
        afficherMot2(XMAX-50, 10, mot);
        if(tc - tframe1000 > 1000)
        {
            tframe1000 = tc;
            lastNbFrames = nbFrames;
        }        /**/


        // Flip the surfaces
        if(imagePrete)
            SDL_Flip(SScreen);

        lastTickCountFrame = tc;
    }
}

void readArgs(int argc, char* args[])
{
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(args[i], "-g") && ++i < argc)
        {
            szGameCfg = args[i];
            cout << "Game config file: " << szGameCfg << endl;
        loadGameCfg(szGameCfg);
        }
        else if(!strcmp(args[i], "-b") && ++i < argc)
        {
            szBoardCfg = args[i];
            cout << "Board config file: " << szBoardCfg << endl;
        }
    }
}

int main(int argc, char* args[])
{
    cout << "Hello!" << endl;

    loadGameCfg(szGameCfg);
    cout << "Game config loaded." << endl;

    readArgs(argc, args);

    PRINT_HERE

    // Initialize
    if(!init())
        return 1;

    PRINT_HERE

    //Load the files
    if( !load_files() )
        return 1;

    PRINT_HERE

    // program main loop
    bool quit = false;
    while (!quit)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_ACTIVEEVENT: // focus lost or gained ?
                if ( event.active.state & SDL_APPINPUTFOCUS )
                    isAppActive = event.active.gain;
                    if(isAppActive)
                    {
                        finSurfaces();
                        loadSurfaces(); // nécessaire pour éviter une perte de données par alt-tab en fullscreen !!
                    }
                break;
                // check for keypresses
            case SDL_KEYDOWN:
                // exit if ESCAPE is pressed
                switch( event.key.keysym.sym )
                {
                    case SDLK_F1: montrerScores = true; break;
                    case SDLK_F10: zeJeu->jMeilleurCourant(); break;
                    case SDLK_F11: // HighSpeed
                        delayFrame = 1000;
                        delayPlay = 1;
                        break;
                    case SDLK_F12: // normalSpeed
                        delayFrame = 40;
                        delayPlay = 20;
                        break;
                    case SDLK_PAUSE: jeuPause = !jeuPause; break;
                    case SDLK_ESCAPE: quit = true; break;
                    case SDLK_TAB: zeJeu->jCourantSuivant(); break;
                    case SDLK_HOME: zeJeu->jCourantLast(); break;
                    default: break;
                }
                break;
            case SDL_KEYUP:
                // exit if ESCAPE is pressed
                switch( event.key.keysym.sym )
                {
                    case SDLK_F1: montrerScores = false; break;
                    default: break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                souris[event.button.button] = true;
                if(event.button.button == SDL_BUTTON_WHEELUP)
                    souris_zaxis++;
                else if(event.button.button == SDL_BUTTON_WHEELDOWN)
                    souris_zaxis--;
                break;
            case SDL_MOUSEBUTTONUP:
                souris[event.button.button] = false;
                break;
            } // end switch
        } // end of message processing

        if(isAppActive)
            updateFrame();

        SDL_Delay(0);

    } // end main loop


    //Free surfaces, fonts and sounds
    //then quit SDL_mixer, SDL_ttf and SDL
    clean_up();

    return 0;
}
