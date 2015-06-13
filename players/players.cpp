#include <map>
#include "players.h"
#include "../jeu.h"
#include "../joueur.h"

#include "humain/humain.h"
#include "simple-bot/simple-bot.h"
#include "ag-bot/ag-bot.h"
// INCLUDE_PLAYER_PLACEHOLDER

using std::map;

typedef Joueur* (*fun_creer_joueur_t)(int);

map<string, fun_creer_joueur_t> joueursClasses;

template<typename T>
Joueur* creerJoueur(int shipType)
{
    return new T(shipType);
}

template<typename T>
void registerJoueur(string clStr)
{
    joueursClasses[clStr] = &creerJoueur<T>;
}

void jeuAjouterJoueur(Jeu* jeu, string clStr, int shipType)
{
    jeu->ajouterJoueur( (*joueursClasses[clStr])(shipType) );
}

void initPlayers(Jeu* jeu)
{
    registerJoueur<Humain>("Humain");
    registerJoueur<SimpleBot>("SimpleBot");
    registerJoueur<AGBot>("AGBot");
    // REGISTER_PLAYER_PLACEHOLDER
}

void endPlayers(Jeu* jeu)
{
}
