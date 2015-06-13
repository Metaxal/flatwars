#include <math.h>
#include <fstream>
#include <sstream>
#include "humain.h"
#include "../../son.h"
#include "../../souris.h"
#include "../../main.h"

using std::ifstream;
using std::stringstream;

const int mouseXCenter = 200; // XMAX/2  // Doesn't work if XMAX=1920?!

Humain::Humain(int numShip)
:    Joueur(numShip),
    _radarOn(false)
{
    setNom("Boniface");
    KbForward = SDLK_w;
    KbBackward = SDLK_s;
    KbStrafeLeft = SDLK_a;
    KbStrafeRight = SDLK_d;
    KbTurnLeft = SDLK_LEFT;
    KbTurnRight = SDLK_RIGHT;
    KbFire1 = SDLK_RCTRL;
    KbFire2 = SDLK_KP0;
    KbRadar = SDLK_r;
    KbScores = SDLK_F1;
    KbArmeSuivante = SDLK_e;


    loadPlayerCfg("cfg/player1.cfg");
    loadKbCfg("cfg/kb.cfg");

}

void Humain::loadPlayerCfg(const char* fich)
{
    ifstream ifs(fich);

    char ligne[5000];
    while(!ifs.eof())
    {
        ifs.getline(ligne, 500, '\t');
        if(!strcmp(ligne, "NAME"))
        {
            ifs.getline(ligne, 500, '\"');
            ifs.getline(ligne, 500, '\"');
            setNom(ligne);
        }


        ifs.getline(ligne, 500);
    }
}

// See cfg/kb-config.cpp for generating the kb.cfg file
void Humain::loadKbCfg(const char* fich)
{
    ifstream ifs(fich);

    char ligne[5000];
    while(!ifs.eof())
    {
        // http://www.libsdl.org/tmp/SDL-1.3-docs/SDL__keyboard_8h.html
        int touche = -1;
        ifs.getline(ligne, 500, '=');
        ifs >> touche;

        if(!strcmp(ligne, "FORWARD"))
            KbForward = touche;
        else if(!strcmp(ligne, "BACKWARD"))
            KbBackward = touche;
        else if(!strcmp(ligne, "STRAFE_LEFT"))
            KbStrafeLeft = touche;
        else if(!strcmp(ligne, "STRAFE_RIGHT"))
            KbStrafeRight = touche;
        else if(!strcmp(ligne, "TURN_LEFT"))
            KbTurnLeft = touche;
        else if(!strcmp(ligne, "TURN_RIGHT"))
            KbTurnRight = touche;
        else if(!strcmp(ligne, "FIRE1"))
            KbFire1 = touche;
        else if(!strcmp(ligne, "FIRE2"))
            KbFire2 = touche;
        else if(!strcmp(ligne, "RADAR"))
            KbRadar = touche;
        else if(!strcmp(ligne, "NEXT_WEAPON"))
            KbArmeSuivante = touche;

        ifs.getline(ligne, 500); // flush the rest of the line
    }
}

void Humain::radar()
{
    afficherLettre(120, 120, '*');

    for(int i = 0; i < nbJoueurs(); i++)
    {
        Joueur* j = joueurs(i);
        int dx = abs(x()-j->x());
        int dy = abs(y()-j->y());

        if(dx + dy < 4000 && j != this) // 20 cases a la ronde
        {
            double ang = atan2(j->y()-y(), j->x()-x());

            afficherLettre(120 + ((100*dx)/4000)*cos(ang), 120 + ((100*dy)/4000)*sin(ang), '\'');
        }
    }

}
/*
void Humain::afficherScores()
{
    char mot[50];

    SDL_Rect r;

    r.y = 69;
    r.x = 1;
    r.h = 13;
    r.w = 270;

    afficherBarre2(XMAX/2-160, 0, &r);

    afficherMot2(XMAX/2-15, 1, "Frags Deaths");


    for(int i = 0; i < nbJoueurs(); i++)
    {
        int yg = i*15+20;
        Joueur* j = joueurs(i);

        if(j == this)
        {
            r.y = 40;
            r.x = 1;
            r.h = 13;
            r.w = 270;
            afficherBarre2(XMAX/2-160, yg-1, &r);
        }

        afficherMot2(XMAX/2-140, yg, j->nom());

        itoa(j->score(), mot, 10);
        afficherMot2(XMAX/2, yg, mot);

        itoa(j->nbMorts(), mot, 10);
        afficherMot2(XMAX/2+50, yg, mot);

    }
}*/

void Humain::afficherDists()
{
    /*char mot[50];

    SDL_Rect r;

    r.x = 1;
    r.y = 69;
    r.w = 270;
    r.h = 5;

    for(double i = -90; i < 90; )
    {
        double dx = cos( ((angle()+i)*PI)/180 )*10; // *48;
        double dy = sin( ((angle()+i)*PI)/180 )*10; // *48;

        int nbc = distAugAvantOccupe(dx, dy);
        if(nbc > 500) nbc = 500;

        itoa(nbc, mot, 10);
        afficherMot2(10, ((i+180)/10)*16, mot);
        r.right = r.left + nbc +2; // 250/nbc +2
        afficherBarre(30, ((i+180)/10)*16, &r);

        if(i>-20 && i<20) i+= 1; else i+=20;
    }*/
}

void Humain::OSD()
{
    if(_radarOn)
        radar();
    afficherDists();

    char mot[50];
    //itoa(sqrt(vx()*vx()+vy()*vy())*10, mot, 10);
    snprintf(mot, 50, "%.2f", sqrt(vx()*vx()+vy()*vy())*10);
    afficherMot2(XMAX-50, 50, mot);

}

void Humain::demanderAction()
{

    int xd;
    int yd;
    caseVisee(xd, yd);
    //findFirstCaseAmmo();

    action = 0;

    bool bg, bd;
    int sx, sz;

    //Uint8 sour = SDL_GetMouseState(&sx, NULL);
    SDL_GetMouseState(&sx, NULL);
    sx -= mouseXCenter;
    sz = souris_getZAxis();
        SDL_WarpMouse(mouseXCenter, YMAX/2);
//    SDL_GetRelativeMouseState(NULL, NULL); // pour annuler l'effet de Warp

    //printf("mouse: %d (XMAX=%d, XMAX/2=%d, sx_before=%d)\n", sx, XMAX, XMAX/2, sx_before);

    bg = souris[SDL_BUTTON_LEFT];
    bd = souris[SDL_BUTTON_RIGHT];

    //sourisGetXY(sx, sy, sz, bg, bd);
    tourner(sx);
    if(sz < 0)
        armeSuivante();
    else if(sz > 0)
        armePrecedente();

    if(bg)
        action |= FIRE1;
    if(bd)
        action |= FIRE2;

    Uint8* keystates = SDL_GetKeyState( NULL );
    //DIGetKeys();
    if(keystates[KbForward])
        action |= FORWARD;
    if(keystates[KbBackward])
        action |= BACKWARD;
    if(keystates[KbStrafeLeft])
        action |= STRAFE_LEFT;
    if(keystates[KbStrafeRight])
        action |= STRAFE_RIGHT;
    if(keystates[KbTurnLeft])
        action |= TURN_LEFT;
    if(keystates[KbTurnRight])
        action |= TURN_RIGHT;
    if(keystates[KbFire1])
        action |= FIRE1;
    else if(keystates[KbFire2])
        action |= FIRE2;

    static bool aS = true;
    if(keystates[KbArmeSuivante])
    {
        if(aS)
            armeSuivante();
        aS = false;
    }
    else
        aS = true;

    static bool rd = false;
    if(keystates[KbRadar])
    {
        if(rd)
        {
            _radarOn = !_radarOn;
            printf("Turning radar %s\n", _radarOn?"on":"off");
        }
        rd = false;
    }
    else
        rd = true;


    /*static bool sc = false;
    if(keystates[KbScores])
    {
        if(sc)
            initFeuilleScores();
        else
            afficherFeuilleScores();
        sc = false;
    }
    else
        sc = true;*/
}
