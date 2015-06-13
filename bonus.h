#ifndef BONUS_H
#define BONUS_H

#include "SDL/SDL.h"
#include "joueur.h"
#include "jeu.h"
#include "affichable.h"
#include "clonable.h"
#include <string>

using std::string;

#define ATTENTE_INIT    200

class Joueur;
class Jeu;

/*
*    Classe virtuelle dont vont deriver tous les bonus
*/
class Bonus : public Affichable, public Clonable
{
protected:
    int numT;
    int attente;
public:
    Bonus();

    virtual string name() =0;

    void setNumT(int i) { numT = i; }
    void agir(Joueur* j);
    virtual bool bonusAgir(Joueur* j) =0;
    bool affichable();
    void decAttente() { if(attente > 0) attente--; }

    // Probability of occurrence on the map, w.r.t. its size, over 10000.
    virtual unsigned int probaOcc() { return 1000; }

    virtual ~Bonus() {}

};


#endif
