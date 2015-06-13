#ifndef SIMPLE_BOT_H
#define SIMPLE_BOT_H

#include "../../joueur.h"

class SimpleBot : public Joueur
{
protected:
    int monAction;
    int decompte;
    int atourne;
    int _mode;
    int _modePrev;
    int _turnAlea;
    int _timerAlea;
    int _timerAmmo;
    /*static*/ Joueur* _cible;

    int _xCible;
    int _yCible;
public:
    SimpleBot(int numShip);
    void setAction(int ac);
    void changerCible();
    virtual void demanderAction();
    template<typename T> // le type de mbonus qu'on cherche
        T* findFirstCaseAmmo();
    int dirigerVers(int cx, int cy);
    virtual void mourir(Joueur* tueur);
    virtual void revivre() {}
};

#endif
