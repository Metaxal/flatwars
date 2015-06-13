#ifndef ARME_H
#define ARME_H

#include "jeu.h"
#include "bullet.h"
#include "affichable.h"
#include "clonable.h"
#include <string>

using std::string;

//#define NB_MAX_ARMES    64

#define DXARME        48
#define    DYARME        48

class Joueur;
class Arme;
class Bullet;

/*
*    Classe virtuelle dont vont deriver toutes les armes
*/
class Arme : public Affichable, public Clonable
{
protected:
    static int _numT;
    int _rateInit1;
    int _rate1;
    int _rateInit2;
    int _rate2;
    int _munitionsInit;
    int _munitionsMax;
    int _munitions;
    Joueur* _proprio;
    //SDL_Rect _RECTImg;
    //static SDL_Surface* _surface;

protected:
    bool decMunitions1(int n);
    bool decMunitions2(int n);

public:
    Arme();
    virtual ~Arme();
    
    virtual string name() =0;

    void init();
    void setProprio(Joueur* p) { _proprio = p; }
    static void setNumT(int n) { _numT = n; }
    static int numT() { return _numT; }
    void decRate() { if(_rate1 > 0) _rate1--; if(_rate2 > 0) _rate2--;}
    bool incMunitions(int m);
    int munitions() { return _munitions; }
    void tireBullet(Bullet* bal, int dangle = 0, int dxg = 0, int dyg = 0);
    void jouerSonArme(int s);
    virtual Arme* clone() =0;
    virtual void fire1() =0;
    virtual void fire2() =0;
    virtual void noFire() {}

};


#endif
