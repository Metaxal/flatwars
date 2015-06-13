#ifndef PLAYERS_H
#define PLAYERS_H

#include <string>

using std::string;

class Jeu;

template<typename T> 
void registerJoueur(string clStr);
void jeuAjouterJoueur(Jeu* jeu, string clStr, int shipType);

void initPlayers(Jeu* jeu);
void endPlayers(Jeu* jeu);

#endif
