#ifndef AGBOT_H
#define AGBOT_H

#include <vector>
#include "../../joueur.h"

using std::vector;


struct Instructions
{
    enum Inst
    {
        turn_left, turn_right, forward, backward, fire1, fire2, strafe_left, strafe_right,
        next_weapon,
        findAmmo, findHealth, findTarget, toward,
        ifrand4, ifNoAmmo, ifHealthLow, ifSpeedLow, ifAtWall,
        pause,
        nope,
        size
    };
    // ifrand4 : 1 chance sur 4 d'effectuer l'instruction suivante
    // pause : genre de break : on arrête les calculs, qu'on reprendra à la prochaine exécution
    // nope : permet de réduire la taille du code si les instructions sont mutées en nope
};

class AGBot : public Joueur
{
private:
protected:
    vector<Instructions::Inst> _code;
    vector<Instructions::Inst> _exec;
    unsigned int _instCourant;
    bool _test; // pour la conditionnelle

    int _xCible;
    int _yCible;
    int _xgCible;
    int _ygCible;
    Joueur* _jCible;

    // pour effectuer les modifications en "doublebuffering" : elles ne prennent effet qu'à la résurrection
    // le temps du purgatoire devrait suffir à effectuer les modifs sans effet de bord
    int _numShipNext;
    vector<Instructions::Inst> _codeNext;

public:
    AGBot(int numShip); // ajout d'un nouveau bot tout neuf, ne descendant de personne
    virtual ~AGBot();

    void initAlea();

    void croisement(AGBot* agb);
    void mutation();
    void reprodAsexuee();

    void initAGBot();

    template<typename T> // le type de mbonus qu'on cherche
        T* findFirst();
    void changerCible();
    int dirigerVers(int cx, int cy);

    bool execCode(int inst, int& i);
	virtual void demanderAction();
    virtual void OSD();
    
	virtual void mourir(Joueur* tueur);
    virtual void revivre();

    void afficherInst();
};



#endif // AGBOT_H
