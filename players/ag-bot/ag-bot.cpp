#include <math.h>
#include <iomanip>
#include <sstream>
#include "ag-bot.h"
#include "../../jeubot.h"
#include "../../ammo.h"
#include "../../outils.h"
#include "../../items/life/life-bonus.h"

using std::stringstream;
using std::setw;

const char* chInst[] = {
    "turn_left","turn_right","forward","backward","fire1","fire2","strafe_left","strafe_right",
    "next_weapon",
    "findAmmo", "findHealth", "findTarget", "toward",
    "ifrand4", "ifNoAmmo", "ifHealthLow", "ifSpeedLow", "ifAtWall",
    "pause",
    "nope",
    "size"
    };


static int nbInstParTour = 100;

//static int tailleUnDemi = 20; // paramètre de croisement
/* Explication :
lors du croisement :
        int ptcoup = rand()%(courant->_code.size()-n+tailleUnDemi) +n;
si le code fait la même taille que tailleUnDemi, il y a 1 chance sur deux de placer le point de croisement
en dehors du tableau (et donc d'arrêter les changements de points de croisement)
Le nombre de croisements est alors dépendant de la taille du code.

Si lors du croisement, on fait
        int ptcoup = rand()%((courant->_code.size()-n)*2) +n;
alors le nombre de points de croisement est indépendant de la taille du code (ne me semble pas mieux, mais à voir)
*/

static int tauxMutation = 500;



AGBot::AGBot(int numShip)
:   Joueur(numShip),
    _xCible(0),
    _yCible(0),
    _xgCible(0),
    _ygCible(0),
    _jCible(NULL),
    _numShipNext(numShip)
{
    setNom("Gen 0");

    initAlea();
}

AGBot::~AGBot()
{
}

void AGBot::initAlea()
{
    _code.clear();

    int nbi = rand() % (nbInstParTour - 10) + 10;
    for(int i = 0; i < nbi; i++)
        _code.push_back((Instructions::Inst)(rand() % Instructions::size));

    initAGBot();
}

/*
    Croisement un peu spécial !
    on croise entre nous-même et notre assassin
    (on se fait violer quoi !!)

    Ce qui est génial, c'est qu'il n'y a alors aucune notion d'évaluation d'un individu (quoiqu'on dit tuer = bien (hum...))
    C'est plus ou moins de la co-évolution

    Petit problème : on risque d'avoir des comportements à suicide pour perpétrer l'espèce !
    (ce qui est contradictoire)
    Dans ce cas, on génère un nouvel individu complètement. Na !
*/
void AGBot::croisement(AGBot* agb)
{

    _codeNext.clear();

    AGBot* agb1 = agb;
    AGBot* agb2 = this;

    AGBot* courant = agb1;

    // croisement normal à deux parents quelconques
    unsigned int n = 0;
    while(n < courant->_code.size())
    {
        //int ptcoup = rand()%(courant->_code.size()-n+tailleUnDemi) +n;
        //int ptcoup = rand()%100 +n; // un point de mutation toutes les 50 instructions environ
        unsigned int ptcoup = courant->_code.size() +1; // TEST : PAS DE CROISEMENT !
        if(ptcoup > courant->_code.size())
            ptcoup = courant->_code.size();

        for( ; n < ptcoup; n++)
            if(courant->_code[n] != Instructions::nope)
                _codeNext.push_back(courant->_code[n]);

        if(courant == agb1)
            courant = agb2;
        else
            courant = agb1;
    }

    _numShipNext = courant->ship()->num();

    mutation();
}

void AGBot::mutation()
{
    if(rand()%10000 < tauxMutation)
        ship()->initVaisseau(rand()%5);

    for(unsigned int i = 0; i < _codeNext.size(); i++)
        if(rand()%10000 < tauxMutation)
            _codeNext[i] = (Instructions::Inst)(rand()%Instructions::size);

    // augmentation et diminution de la taille du code ??
    // on pourrait le faire au moment de la copie dans _code
}

void AGBot::reprodAsexuee()
{
    _codeNext.assign(_code.begin(), _code.end());

    mutation();
}

void AGBot::initAGBot()
{
    _instCourant = 0;
    _test = true;
    _exec.clear();
}

template<typename T> // le type de bonus qu'on cherche
T* AGBot::findFirst()
{
    int anx, any;
    dir(anx, any);

    int decXinit = anx;
    int decYinit = any;

    int xinit = xg2xc(x()+decXinit);
    int yinit = yg2yc(y()+decYinit);

    int dx = decYinit;
    int dy = -decXinit;

    int xd = 0;
    int yd = 0;

    int nb = 0;
    for(int j = 0; j < 20; j++)
    {
        int n = (3-abs(decXinit)-abs(decYinit))*j+1;
        int xd2 = xd;
        int yd2 = yd;
        for(int i=1; i < n; i++) // on commence à 1 pour éviter de reprendre le bonus sur lequel on est...
        {
            int casex = xinit+xd2;
            int casey = yinit+yd2;
            if(!caseValide(casex, casey))
                continue;
            T* bo = dynamic_cast<T*>(caseBonus(casex, casey));
            if(bo)
                if(bo->affichable()) // le bonus est actif
                {
                    _xCible = casex;
                    _yCible = casey;
                    _xgCible = xc2xg(_xCible);
                    _ygCible = yc2yg(_yCible);
                    return bo;
                    /*stringstream mot;
                    mot << nb;
                    afficherMot(xc2xg(xd2)+XMAX/2, yc2yg(yd2)+YMAX/2, mot.str());*/
                }
            xd2+=dx;
            yd2+=dy;
            nb++;
        }
        xd += signe(-dx-dy);
        yd += signe( dx-dy);
    }

    return NULL; //was: false
}

void AGBot::changerCible()
{
    Joueur* c = _jCible;
    int dmin = 10000;

    for(int i = 0; i < nbJoueurs(); i++)
    {
        Joueur* j = joueurs(i);
        if(j == this || j->mort())
            continue;

        int d = abs(j->x()-x()) + abs(j->y()-y());
        if(d < dmin)
        {
            dmin = d;
            c = j;
        }

    }

    _jCible = c;
}

// cx et cy sont des coordonnées graphiques et non de case.
int AGBot::dirigerVers(int cx, int cy)
{
    double angCible = (360*atan2(cy-y(),cx-x())) / (2*3.141592654);
    //int da = ((int)angCible-angle()+180*3)%360;
    int da = ((((int)angCible+180*3)%360 - (angle()+180*3)%360)+180*3)%360;

    int act = 0;

    int d = abs(cx-x()) + abs(cx-y());
    //if(d > 300)
        act |= FORWARD;

    if(da > 180+25)
        act |= TURN_RIGHT; // on se rapproche grossierement de la cible
    else if(da < 180-25)
        act |= TURN_LEFT;
    else if(d < 1000) // etre assez pres pour tirer*/
    {
        tourner(da-180);    // on affine la visée
        //action |= FIRE1;
        //action |= STRAFE_LEFT;
    }

    return act;
}

// i permet de modifier le nombre d'opérations que prend l'instruction
bool AGBot::execCode(int inst, int& i)
{
    if(!_test)
    {
        _test = true;
        return true;
    }

    switch(_code[inst])
    {
        case Instructions::turn_left: action ^= TURN_LEFT; break;
        case Instructions::turn_right: action ^= TURN_RIGHT; break;
        case Instructions::forward: action ^= FORWARD; break;
        case Instructions::backward: action ^= BACKWARD; break;
        case Instructions::fire1: action ^= FIRE1; break;
        case Instructions::fire2: action ^= FIRE2; break;
        case Instructions::strafe_left: action ^= STRAFE_LEFT; break;
        case Instructions::strafe_right: action ^= STRAFE_RIGHT; break;
        case Instructions::next_weapon: armeSuivante(); break;
        case Instructions::toward: action |= dirigerVers(_xgCible, _ygCible); break;
        case Instructions::findAmmo: findFirst<Ammo>(); break;
        case Instructions::findHealth: findFirst<LifeBonus>(); break;
        case Instructions::findTarget:changerCible(); break;
        case Instructions::ifrand4: _test = (rand()%4 == 0); break;
        case Instructions::ifNoAmmo: _test = (munitions(-1) == 0); break;
        case Instructions::ifHealthLow: _test = (vie() <= ship()->vieInit()*0.25); break;
        case Instructions::ifSpeedLow: _test = (abs(vx()) < 0.01 && abs(vy()) < 0.01); break;
        case Instructions::ifAtWall: int xc, yc; caseVisee(xc, yc); _test = caseMur(xc, yc); break;
        case Instructions::pause: return false;
        default:
            ;
    }

    return true;
}

void AGBot::demanderAction()
{
    if(mort())
    {
        action = FORWARD;
        return;
    }

    if(_jCible != NULL)
    {
        if(_jCible->mort())
            _jCible = NULL;
        else
        {
            _xgCible = _jCible->x();
            _ygCible = _jCible->y();
        }
    }

    bool arret = false;
    _exec.clear();
    _instCourant = 0;
    for(int i = 0; i < nbInstParTour && !arret; i++)
    {
        if(!execCode(_instCourant, i))
            arret = true;

        _instCourant++;
        if(_instCourant == _code.size())
        {
            _exec.clear();
            _instCourant = 0;
        }
    }
}

void AGBot::OSD()
{
    if(jCourant()) // affichage seulement si joueur courant
    {
        Uint8* keystates = SDL_GetKeyState( NULL );
        if(keystates[SDLK_F2])
            afficherInst();

        afficherMot(_xgCible-xEcran(), _ygCible-yEcran(), "*");
    }
}

void AGBot::mourir(Joueur* tueur)
{
    AGBot* agb = dynamic_cast<AGBot*>(tueur);
    if(tueur == this || !agb) // si on s'est fait tué par un individu d'une autre espèce, on ne fait qu'une mutation
        reprodAsexuee();
    else if(agb && tueur != this) // on ne croise qu'avec des individus de la même espèce ! (des AGBots quoi)
        croisement(agb);
}

void AGBot::revivre()
{
    _code.assign(_codeNext.begin(), _codeNext.end());
    ship()->initVaisseau(_numShipNext); // on change de vaisseau !
    // une chance sur 2 de garder le même ?

    initAGBot();
}

void AGBot::afficherInst()
{
    SDL_Rect r;

    r.x = 1;
    r.y = 69;
    r.w = 270;
    r.h = 13;

    int nbjparcol = YMAX/(DYLETTRE2*1.5)-2;
    for(unsigned int i = 0; i < _code.size(); i++)
    {
        int xg = (i/nbjparcol)*280+40;
        int yg = (i%nbjparcol)*15+20;

        if(i == _instCourant)
            r.y = 40;
        else
            r.y = 54;

        if(i == _instCourant)
            afficherBarre2(xg-20, yg-1, &r);

        stringstream s;
            //int ci = _code[i];
        s << setw(3) << i << " "
            << (i == _instCourant?"[[":"")
            << chInst[_code[i]]
            << (i == _instCourant?"]]":"")
            ;
        afficherMot2(xg, yg, s.str());
    }

    if(strcmp(chInst[Instructions::size], "size") != -1)
        afficherMot(XMAX/2, YMAX/2, "Error: chInst[Instructions::size] != \"size\"");
}

