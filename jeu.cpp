#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>
#include "jeu.h"
#include "jeubot.h"
#include "ammo.h"

// Armes, ammos et bonus:
#include "items/items.h"
// Joueurs:
#include "players/players.h"

using namespace std;

//Jeu* Jeu::_instance = NULL;

int dirs[2][8] = {{-1, 0, 1, 1, 1, 0, -1, -1}, {-1, -1, -1, 0, 1, 1, 1, 0}};

bool pointCollision(int x, int y, int xb1, int yb1, int xb2, int yb2)
{
    return x >= xb1 && x <= xb2
        &&    y >= yb1 && y <= yb2;
}

bool rectCollision(int xa1, int ya1, int xa2, int ya2, int xb1, int yb1, int xb2, int yb2)
{
    return
        pointCollision(xa1, ya1,  xb1,  yb1,  xb2,  yb2) ||
        pointCollision(xa1, ya2,  xb1,  yb1,  xb2,  yb2) ||
        pointCollision(xa2, ya1,  xb1,  yb1,  xb2,  yb2) ||
        pointCollision(xa2, ya2,  xb1,  yb1,  xb2,  yb2) ||
        pointCollision(xb1, yb1,  xa1,  ya1,  xa2,  ya2); //cas ou le grand rectangle englobe le petit
    // il manque le cas ou les deux rectangles s'entrecoupent sans qu'aucun point
    // ne soit a l'interieur de l'un ou de l'autre. (rectangles + longs que larges)


}

int xc2xg(int xc) {    return xc*DXCASE; }
int yc2yg(int yc) {    return yc*DYCASE; }
int xg2xc(int xg) {    return xg/DXCASE; }
int yg2yc(int yg) {    return yg/DYCASE; }
int xg2xc(double xg) {    return xg2xc((int)xg); }
int yg2yc(double yg) {    return yg2yc((int)yg); }

Jeu::Jeu()
:    _jCourant(0),
    _nbCasesX(XCMAX), _nbCasesY(YCMAX),
    _scoreMode(false)
{
    int i;

    RECTViseur.x = 0;
    RECTViseur.y = 263;
    RECTViseur.w = 8;
    RECTViseur.h = 8;

    for(i = 0; i < NB_IMG_EXPL; i++)
    {
        RECTExpl[i].x = (DXSHIP+1)*i;
        RECTExpl[i].y = 272;
        RECTExpl[i].w = DXSHIP;
        RECTExpl[i].h = DYSHIP;
    }

}

void Jeu::jCourantSuivant()
{
    _joueurs[_jCourant]->setJCourant(false);

    int jc2 = _jCourant;
    do
    {
        jc2++;
        jc2 %= _joueurs.size();
    }
    while(_joueurs[jc2] == NULL);

    _jCourant = jc2;
    _joueurs[_jCourant]->setJCourant(true);
}

bool compScore(Joueur* j1, Joueur* j2)
{
    if(j1 == NULL || j2 == NULL)
        cout << "j NULL !!" << endl;
    if(j1->score() > j2->score())
        return true;
    if(j1->score() == j2->score())
        if(j1->nbMorts() < j2->nbMorts())
            return true;

    return false;
}

void Jeu::jMeilleurCourant()
{
    _joueurs[_jCourant]->setJCourant(false);

    vector<Joueur*> jsorted(_joueurs);
    sort(jsorted.begin(), jsorted.end(),  compScore); // ne fonctionne pas bien ?

    int j;
    for(j=0; _joueurs[j] != jsorted[0]; j++)
        ;

    _jCourant = j;
    _joueurs[_jCourant]->setJCourant(true);
}

void Jeu::jCourantLast()
{
    _joueurs[_jCourant]->setJCourant(false);
    _jCourant = _joueurs.size()-1;
    _joueurs[_jCourant]->setJCourant(true);
}

Joueur* Jeu::joueurs(unsigned int i)
{
    if(i < 0 || i >= _joueurs.size())
    {
        cout << "j NULL dans Joueur* Jeu::joueurs(int i)" << endl;
        return NULL;
    }
    else
        return _joueurs[i];
}

/*
*    renvoie vrai si le joueur a reussi a se positioner
*/
bool Jeu::positJoueur(Joueur* j)
{
    int nbTry = 100;
    for(int i = 0; i < nbTry; i++)
    {
        int xc = rand() % (_nbCasesX - 2) + 1;
        int yc = rand() % (_nbCasesY - 2) + 1;
        j->setPos(xc2xg(xc), yc2yg(yc));
        if(!j->collision())
            return true;
    }

    return false;
}

void Jeu::ajouterJoueur(Joueur* j)
{
    j->setZeJeu(this); // tres important !

    PRINT_HERE

    if(!positJoueur(j))
    {
        cout << "Error: Could not place player." << endl;
        exit(-1);
    }

    PRINT_HERE

    _joueurs.push_back(j);
    int i = _joueurs.size()-1;
    j->setNumT(i);
    jCourantSuivant();//_jCourant = i;
}

/*
*    On essaye d'ajouter et si on peut pas, on detruit l'objet considéré
*/
void Jeu::enleverJoueur(unsigned int j)
{
    cout << "enlever joueur ?" << endl;
    delete _joueurs[j];
    _joueurs[j] = _joueurs.back();
    _joueurs.pop_back();
    if(_jCourant == _joueurs.size())
        _jCourant = j;
}



/*
*    On essaye d'ajouter et si on peut pas, on detruit l'objet considéré
*/
void Jeu::ajouterBullet(Bullet* bal)
{
    _bullets.push_back(bal);
    bal->setNumT(_bullets.size()-1);
}


/*
*    suppose que _bullets[b] est valide !!
*/
void Jeu::enleverBullet(unsigned int b)
{
    delete _bullets[b];
    _bullets[b] = _bullets.back();
    _bullets.pop_back();
}

/*
*    Il faut ajouter les joueurs avant d'ajouter une arme !!
*    sinon ils n'auront pas toutes les armes !! (+ bugs... :-)
*    On essaye d'ajouter et si on peut pas, on detruit l'objet considéré
*   (this remarks are obsolete)
*
* Registers a weapon, with the associated bonus
*
*/
void Jeu::registerArme(Arme* arm, Ammo* ammo)
{
    _armes.push_back(arm);
    arm->setNumT(_armes.size()-1);
    registerBonus(ammo);
    ammo->setWeaponNumT(arm->numT());
}

void Jeu::registerBonus(Bonus* bon)
{
    _bonusKinds.push_back(bon);
}

/*
*    On essaye d'ajouter et si on peut pas, on detruit l'objet considéré
*/
void Jeu::ajouterBonus(Bonus* bon, int xc, int yc)
{
    carte[xc][yc] = VIDE_BONUS+_bonus.size();
    _bonus.push_back(bon);
    bon->setNumT(_bonus.size()-1);
}

void Jeu::enleverBonus(unsigned int b)
{
    delete _bonus[b];
    _bonus[b] = _bonus.back();
    _bonus.pop_back();
}



Jeu::~Jeu()
{
    unsigned int i;
    for(i = 0; i < _joueurs.size(); i++)
        enleverJoueur(i);
    for(i = 0; i < _bullets.size(); i++)
        enleverBullet(i);
    for(i = 0; i < _bonus.size(); i++)
        enleverBonus(i);

    Joueur::freeSurfaces();

    endItems(this); // 'this' is still valid here? (probably)

    endPlayers(this);
}

Joueur* Jeu::colBulletJoueur(Bullet* bal)
{
    for(unsigned int i = 0; i < _joueurs.size(); i++)
    {
        Joueur* j = _joueurs[i];
        if(rectCollision(bal->x(), bal->y(), bal->x()+DXBULLET, bal->y()+DYBULLET,
            j->x(), j->y(), j->x()+DXSHIP, j->y()+DYSHIP))
            return j;
    }

    return NULL;
}


void Jeu::loadBoardCfg(const string fich)
{
    _cfgPlayers.clear();

    ::ifstream ifs(fich.c_str());

    char ligne[5000];
    while(!ifs.eof())
    {
        ifs.getline(ligne, 500, '=');
        if(!strcmp(ligne, "NBCASESX"))
        {
            int xm;
            ifs >> xm;
            cout << XMAX << " " << DXCASE << " " << XCMAX << endl;
            if(xm >= XMAX/DXCASE && xm <= XCMAX)
                _nbCasesX = xm;
            cout << "nbCasesX = " << _nbCasesX << " (" << xm << ")" << endl;
        }
        else if(!strcmp(ligne, "NBCASESY"))
        {
            int ym;
            ifs >> ym;
            if(ym >= YMAX/DYCASE && ym <= YCMAX)
                _nbCasesY = ym;
            cout << "nbCasesY = " << _nbCasesY << " (" << ym << ")" << endl;
        }
        else if(!strcmp(ligne, "PLAYER"))
        {
            CfgPlayer c;
            ifs >> c.playerClass;
            ifs >> c.nb;
            _cfgPlayers.push_back(c);
            cout << "Player " << c.playerClass << " × " << c.nb << endl;
        }
        /*else if(!strcmp(ligne, "NBBOTS"))
        {
            int n;
            ifs >> n;
            _nbBotsACreer = n;
            cout << "nbBotsACreer = " << _nbBotsACreer << endl;
        }*/
        else if(!strcmp(ligne, "FLOOR_IMG"))
        {
            ifs >> _szFloor;
            cout << "Floor =  " << _szFloor << endl;
        }

        ifs.getline(ligne, 500);
    }

}


/*
*    Cree des murs aleatoirement dans la carte en essayant de faire un peu d'architecture
*/
void Jeu::murs(int nb)
{
    int xc = rand()%(_nbCasesX-2)+1;
    int yc = rand()%(_nbCasesY-2)+1;
    int vx = 0;
    int vy = 0;

    while(nb != 0)
    {
        xc += vx;
        yc += vy;

        if(rand()%(20) == 0 ||
            xc < 0 || xc >= _nbCasesX || yc < 0 || yc >= _nbCasesY)
        {
            xc = rand()%(_nbCasesX-2)+1;
            yc = rand()%(_nbCasesY-2)+1;
        }

        carte[xc][yc] = MUR;

        if(vx == 0 && vy == 0)
        {
            if(rand()%(2) == 0)
                vx = rand()%(2)*2-1;
            else
                vy = rand()%(2)*2-1;
        }
        else if(vx != 0)
        {
            if(rand()%(10) > 7)
                vx = rand()%(2)*2-1;
            else if(rand()%(10) > 6)
            {
                vx = 0;
                vy = rand()%(2)*2-1;
            }
        }
        else
        {
            if(rand()%(10) > 7)
                vy = rand()%(2)*2-1;
            else if(rand()%(10) > 6)
            {
                vx = rand()%(2)*2-1;
                vy = 0;
            }
        }

        nb--;
    }
}

/*
*    Cherche la premiere case a 1 qui a un voisin a 0
*    Mets toutes les cases voisins (transitivement) a 1
*    si elles etaient a 0.
*/

void voisins(int cart[XCMAX][YCMAX])
{
    list<int*> xcs;
    list<int*> ycs;
    int* p;

    bool trouve = false;

    for(int i = 0; i < XCMAX && !trouve; i++)
    for(int j = 0; j < YCMAX && !trouve; j++)
    if(cart[i][j] == 1)
        for(int k = 0; k < 4; k++)
        {
            int xc2 = i+dirs[0][k*2+1];
            int yc2 = j+dirs[1][k*2+1];
            if(cart[xc2][yc2] == 0)
            {
                p = new int(xc2);
                xcs.push_back(p);
                p = new int(yc2);
                ycs.push_back(p);

                cart[xc2][yc2] = 1;
                trouve = true;
                break;
            }
        }
    if(!trouve)
        return;

    do
    {
        int xxc = *xcs.front();
        delete xcs.front();
        xcs.pop_front();
        int yyc = *ycs.front();
        delete ycs.front();
        ycs.pop_front();



        for(int i = 0; i < 4; i++)
        {
            int xc2 = xxc+dirs[0][i*2+1];
            int yc2 = yyc+dirs[1][i*2+1];
            if(cart[xc2][yc2] == 0)
            {
                p = new int(xc2);
                xcs.push_back(p);
                p = new int(yc2);
                ycs.push_back(p);

                cart[xc2][yc2] = 1;
            }
        }
    }
    while(!xcs.empty());

}

void Jeu::init(const string boardFile)
{
    _nbCasesX = XCMAX;
    _nbCasesY = YCMAX;
    _scoreMode = false;

    PRINT_HERE

    loadBoardCfg(boardFile);
    cout << "Board loaded:" << _nbCasesX << " " << _nbCasesY << endl;


    PRINT_HERE

    int i, j;

    // Toutes les cases sont vides par defaut
    memset(&carte, (int)VIDE, sizeof(carte));

    // Des murs tout autour pout qu'on puisse pas s'echapper !
    for(i = 0; i < _nbCasesX; i++)
    {
        carte[i][0] = MUR;
        carte[i][_nbCasesY-1] = MUR;
    }
    for(i = 0; i < _nbCasesY; i++)
    {
        carte[0][i] = MUR;
        carte[_nbCasesX-1][i] = MUR;
    }


    murs(_nbCasesX*_nbCasesY/15); // pour poser les murs

    PRINT_HERE

    /*
    *    Empeche d'avoir des zones isolées
    */
    int carte2[XCMAX][YCMAX];
    memset(carte2, -1, sizeof(carte2)); // init à mur, avec les bords

    for(i = 1; i < _nbCasesX-1; i++) // pas les bords
    for(j = 1; j < _nbCasesY-1; j++)
    if(caseVide(i, j))
        carte2[i][j] = 0;

    // on met a 1 toutes les cases transitivement voisines a la premiere case vide trouvée
    bool vtrouve = false;
    for(i = 1; i < _nbCasesX-1 && !vtrouve; i++) // pas les bords
    for(j = 1; j < _nbCasesY-1 && !vtrouve; j++)
    if(carte2[i][j] == 0) // premiere case vide
    {
        carte2[i][j] = 1;
        vtrouve = true;
    }//si on trouve pas, on fait rien, mais là, c'est pas terrible

    PRINT_HERE

    bool isole = true;
    while(isole)
    {
        isole = false;

        voisins(carte2);


        for(i = 1; i < _nbCasesX-1 && !isole; i++) // pas les bords
        for(j = 1; j < _nbCasesY-1 && !isole; j++)
        if(carte2[i][j] == 0)        // zone isolée
        {
            if(carte2[i-1][j] == -1 && i != 1)
            {
                carte[i-1][j] = VIDE;
                carte2[i-1][j] = 0;
            }
            else if(carte2[i+1][j] == -1 && i != _nbCasesY-2)
            {
                carte[i+1][j] = VIDE;
                carte2[i+1][j] = 0;
            }
            else
                continue;

            isole = true;
        }

    }
    //fin des zones isolées

    PRINT_HERE

    /*
    *    Empeche d'avoir des murs qui ne se touchent que par la diagonale
    */
    for(i = 1; i < _nbCasesX-1; i++) // pas les bords
    for(j = 1; j < _nbCasesY-1; j++)
    if(caseMur(i, j))
    {
        for(int k = 0; k < 4; k++)
        {
            int k1 = (k*2+7) % 8;
            int k2 = k*2 % 8;
            int k3 = (k*2+1) % 8;
            if(   caseMur(i+dirs[0][k2], j+dirs[1][k2]) &&
                ! caseMur(i+dirs[0][k1], j+dirs[1][k1]) &&
                ! caseMur(i+dirs[0][k3], j+dirs[1][k3]) )
            {
                carte[i][j] = VIDE;    //    ici on n'est pas sur les bords
                i--;
                j--;
                break;
            }
        }
    }
    // fin des murs qui se touchent en diag



    /*
    *    Trouve le sprite du mur adequat en fonction du nb de murs autour
    */
    for(i = 0; i < _nbCasesX; i++) // AVEC les bords
    for(j = 0; j < _nbCasesY; j++)
    if(caseMur(i, j))
    {
        int n = 0;
        int kk[4] = {0, 0, 0, 0};
        int lnum = 0;
        for(int k = 0; k < 4; k++)
        {
            int xcm = i+dirs[0][k*2+1];
            int ycm = j+dirs[1][k*2+1];
            if(xcm >= 0 && xcm < _nbCasesX && ycm >= 0 && ycm < _nbCasesY)
                if(caseMur(xcm, ycm))
                {
                    kk[k] = 1;
                    lnum = k;
                    n++;
                }
        }

        if(n == 1)
            carte[i][j] = MUR+lnum+1;
        else if(n == 2)
        {
            if(kk[0] && kk[2])
                carte[i][j] = MUR+5;
            else if(kk[1] && kk[3])
                carte[i][j] = MUR+6;
            else if(kk[0])
            {
                if(kk[1])
                    carte[i][j] = MUR+7;
                else
                    carte[i][j] = MUR+10;
            }
            else
            {
                if(kk[1])
                    carte[i][j] = MUR+8;
                else
                    carte[i][j] = MUR+9;
            }
        }
        else if(n == 3)
        {
            if(!kk[3]) carte[i][j] = MUR+11;
            if(!kk[0]) carte[i][j] = MUR+12;
            if(!kk[1]) carte[i][j] = MUR+13;
            if(!kk[2]) carte[i][j] = MUR+14;
        }
        else if(n == 4)
            carte[i][j] = MUR+15;


    }
    // fin sprites des murs

    PRINT_HERE

    // Register all weapons and bonus:
    initItems(this);

    for(unsigned int bi = 0; bi < _bonusKinds.size(); bi++)
    {
        Bonus* b = _bonusKinds[bi];
        unsigned int p = (_nbCasesX * _nbCasesY * b->probaOcc()) / 10000;
        printf("proba %s (%u): %u\n", b->name().c_str(), bi, p);
        for(unsigned int i = 0; i < p; i++)
            ajouterBonus((Bonus*)b->clone(),
                rand() % (_nbCasesX - 2) + 1,
                rand() % (_nbCasesY - 2) + 1);
    }

    PRINT_HERE

    if(DEBUG) afficherCarteTxt();

    PRINT_HERE

    initPlayers(this);

    PRINT_HERE

    // Adding players based on the configuration file
    // format in cfg file: PLAYER=<PlayerClass> <number>
    for(unsigned int i = 0; i < _cfgPlayers.size(); i++)
    {
        for(unsigned int n = 0; n < _cfgPlayers[i].nb; n++)
            jeuAjouterJoueur(this, _cfgPlayers[i].playerClass, rand() % 5);
    }

    // The last added player gets the focus
    jeuAjouterJoueur(this, "Humain", OISEAU);

    PRINT_HERE

    for(unsigned int j = 0; j < _joueurs.size(); j++)
    {
        _joueurs[j]->init();
        _joueurs[j]->ajouterArmes(_armes);
    }

    PRINT_HERE

}

void Jeu::afficherScores()
{
    char mot[50];

    SDL_Rect r;

    r.x = 1;
    r.y = 69;
    r.w = 270;
    r.h = 13;

    afficherBarre2(XMAX/2-160, 0, &r);

    afficherMotScores(XMAX/2-15, 1, "Frags Deaths");

    vector<Joueur*> jsorted(_joueurs);

    sort(jsorted.begin(), jsorted.end(),  compScore); // ne fonctionne pas bien !!

    int nbjparcol = YMAX/(DYLETTRE2*1.5)-2;

    for(unsigned int i = 0; i < jsorted.size(); i++)
    {
        int yg = (i%nbjparcol)*15+20;
        int xg = (i/nbjparcol)*280+40;

        if(jsorted[i] == _joueurs[_jCourant])
            r.y = 40;
        else
            r.y = 54;

        if(jsorted[i] == _joueurs[_jCourant])
            afficherBarre2(xg-20, yg-1, &r);

        snprintf(mot, 50, "%d", i);
        afficherMotScores(xg-20, yg, mot);

        afficherMotScores(xg+10, yg, jsorted[i]->nom());

        snprintf(mot, 50, "%d", jsorted[i]->score());
        afficherMotScores(xg+140, yg, mot);

        snprintf(mot, 50, "%d", jsorted[i]->nbMorts());
        afficherMotScores(xg+190, yg, mot);

        snprintf(mot, 50, "%d", jsorted[i]->ship()->num());
        afficherMotScores(xg+220, yg, mot);

    }
}

void Jeu::creerCarte()
{
    for(int i = 0; i < _nbCasesX; i++)
    for(int j = 0; j < _nbCasesY; j++)
    {
        int xg = xc2xg(i);
        int yg = yc2yg(j);

        afficherSol(xg, yg);

        int m = caseMur(i, j);
        if(m)
            afficherMur(xg, yg, m);
    }
}

void Jeu::afficherCarteTxt()
{
    cout << "_nbCasesX=" << _nbCasesX << "  _nbCasesY=" << _nbCasesY << endl;
    for(int i = 0; i < _nbCasesX; i++)
    {
        for(int j = 0; j < _nbCasesY; j++)
        {
            printf("%5d", carte[i][j]);
        }
        cout << endl;
    }
}

void Jeu::afficherCarte(SDL_Surface* SScreen)
{
    _xEcran = 0;
    _yEcran = 0;

    int xgmax = xc2xg(_nbCasesX);
    int ygmax = yc2yg(_nbCasesY);

    Joueur* jC;
    if((jC = _joueurs[_jCourant]) != NULL)
    {
        int x = jC->x()+DXSHIP/2;
        int y = jC->y()+DYSHIP/2;

        int marge = 0;
        if(x + marge < XMAX/2)
            _xEcran = -marge;
        else if(x + XMAX/2 - marge > xgmax)
            _xEcran = xgmax - XMAX + marge;
        else
            _xEcran = x - XMAX/2;

        if(y + marge < YMAX/2)
            _yEcran = -marge;
        else if(y + YMAX/2 - marge > ygmax)
            _yEcran = ygmax - YMAX + marge;
        else
            _yEcran = y - YMAX/2;

        for(int i = max(0, xg2xc(_xEcran)); i < min(_nbCasesX, xg2xc(_xEcran+XMAX)+1); i++)
        for(int j = max(0, yg2yc(_yEcran)); j < min(_nbCasesY, yg2yc(_yEcran+YMAX)+1); j++)
        {
            int xg = xc2xg(i)-_xEcran;
            int yg = yc2yg(j)-_yEcran;
            afficherSol(xg, yg);

            Bonus* bon = caseBonus(i, j);
            if(bon != NULL)
                if(bon->affichable())
                    bon->afficher(SScreen, xg, yg);

            int m = caseMur(i, j);
            if(m)
                afficherMur(xg, yg, m);
        }


        afficherJoueurs(_xEcran, _yEcran);
        afficherBullets(SScreen, _xEcran, _yEcran);

        // Affichage du viseur
        double ang = (jC->angle()*2*PI)/360;
        afficherCase(x-_xEcran-DXBULLET/2+DXSHIP*2*cos(ang), y-_yEcran-DYBULLET/2+(double)DYSHIP*2*sin(ang), &RECTViseur);

        jC->afficherHUD(SScreen);
    }// fin : jC != NULL

}

void Jeu::afficherJoueurs(int _xEcran, int _yEcran)
{
    Joueur* j;
    for(unsigned int i = 0; i < _joueurs.size(); i++)
    {
        j = _joueurs[i];
        SDL_Rect r = j->RECTImg();
        afficherCase(j->x()-_xEcran, j->y()-_yEcran, &r);
        if(j->revivable())
            afficherCase(j->x()-_xEcran, j->y()-_yEcran, &(RECTExpl[NB_IMG_EXPL-1]));
        else
        if(j->touche())
        {
            afficherCase(j->x()-_xEcran, j->y()-_yEcran, &(RECTExpl[rand()%(NB_IMG_EXPL-1)]));
        }

        int xc, yc;
        j->caseVisee(xc, yc);
        if(occupe(xc, yc))
            afficherCase(j->x()-_xEcran+DXCASE, j->y()-_yEcran, &(RECTExpl[1]));

        j->OSD();
    }
}

void Jeu::afficherBullets(SDL_Surface* SScreen, int _xEcran, int _yEcran)
{
    for(unsigned int i = 0; i < _bullets.size(); i++)
    {
        Bullet* b = _bullets[i];
        b->afficher(SScreen, b->x()-_xEcran, b->y()-_yEcran);
    }
}

void Jeu::jouer()
{
    unsigned int i;
    Joueur* jo;

    for(i = 0; i < _bonus.size(); i++)
        _bonus[i]->decAttente();

    unsigned int nbj = _joueurs.size();
    for(i = 0; i < nbj; i++)
        if( (jo = _joueurs[i]) != NULL)
        {
            if(jo->touche())
                jo->decTouche();

            if(jo->mort())
            {
                jo->purgatoire();
                if(jo->bRevivre())
                {
                    jo->init();
                    if(!positJoueur(jo))
                        enleverJoueur(jo->numT());
                }
            }
            else
                jo->agir();
        }

    for(i = 0; i < _joueurs.size(); i++)
        if(_joueurs[i] != NULL)
            _joueurs[i]->arriver();

    for(i = 0; i < _bullets.size(); i++)
        if(_bullets[i] != NULL)
            if(_bullets[i]->agir())    // la bullet doit etre enlevée ?
            {
                enleverBullet(i);
                i--;    // a cause d'enleverBullet qui prend le dernier et le met ici !
            }

    for(i = 0; i < _joueurs.size(); i++)
        if(_joueurs[i] != NULL)
            _joueurs[i]->partir();

}

bool Jeu::caseValide(int xc, int yc)
{
    return xc >=0 && xc <= _nbCasesX && yc >=0 && yc <= _nbCasesY;
}

Bonus* Jeu::caseBonus(int xc, int yc)
{
    int n = carte[xc][yc];
    if( (n >= VIDE_BONUS) && (n < VIDE_BONUS+NB_MAX_BONUS) )
        return _bonus[n-VIDE_BONUS];
    else
        return NULL;
}

int Jeu::caseMur(int xc, int yc)
{
    // on se fiche de savoir si la case est occupée ou non
    // donc on enleve le bit le signifiant

    // il faut caster en int !!!!!!!!!!!!!!!
    int c = carte[xc][yc] & ~((int)OCCUPE);

    if(c >= MUR && c < VIDE_BONUS)
        return c-MUR+1;
    else
        return 0;
}

/*
*    Teste si la case est completement vide, sans aucun bonus
*/
bool Jeu::caseVide(int xc, int yc)
{
    return (carte[xc][yc] & ~((int)OCCUPE)) == VIDE;
}

bool Jeu::occupe(int xc, int yc)
{
    // les () sont obligatoires !!!
    return (carte[xc][yc] & ((int)OCCUPE)) != 0;
}

void Jeu::arriver(int xc, int yc)
{
    carte[xc][yc] |= OCCUPE;
}

void Jeu::partir(int xc, int yc)
{
    // il faut caster en int !!!
    carte[xc][yc] &= ~((int)OCCUPE);
}


bool Jeu::collisionsJoueur(Joueur* j)
{
    bool col = false;
    for(unsigned int i = 0; i < _joueurs.size(); i++)
        if(_joueurs[i] != j)
            col |= j->collisionJoueur(_joueurs[i]);

    return col;
}

/*
Returns the player that is the closest from (xg, yg),
except player saufJoueur.
*/
Joueur* Jeu::joueurPlusProche(int xg, int yg, Joueur* saufJoueur)
{
    Joueur* joueurMin = NULL;
    int distMin = -1;
    for(unsigned int i = 0; i < _joueurs.size(); i++)
    {
        Joueur* j = _joueurs[i];
        if(j != saufJoueur)
        {
            int dx = (xg - j->x());
            int dy = (yg - j->y());
            double d = dx * dx + dy * dy;
            if(joueurMin == NULL || d < distMin)
            {
                joueurMin = j;
                distMin = d;
            }
        }
    }
    return joueurMin;
}


