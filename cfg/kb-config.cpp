#include "SDL/SDL.h"
/*
Compile:
$ g++ -o kb-config kb-config.cpp -lSDL
Run:
$ ./kb-config

then make sure the window has the focused, and press the keys asked for in the console.
Generates the file kb.cfg.
*/

#include <iostream>
#include <fstream>

using namespace std;

int nbActions = 10;
const char* actions[] = {"FORWARD", "BACKWARD", "STRAFE_LEFT", "STRAFE_RIGHT", "TURN_LEFT", "TURN_RIGHT", "FIRE1", "FIRE2", "RADAR", "NEXT_WEAPON"};

void askKey(int n)
{
    printf("%s: ", actions[n]);
    fflush(stdout);
}

void DisplayState(SDL_KeyboardEvent *key)
{
    if (key->type == SDL_KEYUP)
        printf("RELEASED: ");
    else
        printf("PRESSED: ");
 
}

void DisplayModifiers(SDL_KeyboardEvent *key)
{
    SDLMod modifier = key->keysym.mod;
    if( modifier & KMOD_NUM ) printf( "NUMLOCK " );
    if( modifier & KMOD_CAPS ) printf( "CAPSLOCK " );
    if( modifier & KMOD_MODE ) printf( "MODE " );
    if( modifier & KMOD_LCTRL ) printf( "LCTRL " );
    if( modifier & KMOD_RCTRL ) printf( "RCTRL " );
    if( modifier & KMOD_LSHIFT ) printf( "LSHIFT " );
    if( modifier & KMOD_RSHIFT ) printf( "RSHIFT " );
    if( modifier & KMOD_LALT ) printf( "LALT " );
    if( modifier & KMOD_RALT ) printf( "RALT " );
    if( modifier & KMOD_LMETA ) printf( "LMETA " );
    if( modifier & KMOD_RMETA ) printf( "RMETA " );
}

void DisplayKey(SDL_KeyboardEvent *key)
{
    printf( "%s (%d)\n", SDL_GetKeyName(key->keysym.sym), key->keysym.sym);
}
 
 
 int main ( int argc, char** argv )
{
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 800x600 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    /*SDL_Surface* bmp = SDL_LoadBMP("cb.bmp");
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - bmp->w) / 2;
    dstrect.y = (screen->h - bmp->h) / 2;
    */
    
    ofstream cfgFile("kb.cfg");
    

    // program main loop
    int nAct = 0;
    askKey(nAct);

    bool done = false;
    while (!done)
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
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                //DisplayState(&event.key);
                //DisplayModifiers(&event.key);
                DisplayKey(&event.key);
                cfgFile << actions[nAct] << "=" << event.key.keysym.sym << endl;
                askKey(++nAct);
                if(nAct == nbActions || event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            case SDL_KEYUP:
                break;
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        //SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        //SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        //SDL_Flip(screen);
    } // end main loop
    
    cfgFile.close();

    // free loaded bitmap
    //SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}

