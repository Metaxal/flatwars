#ifndef HUMAIN2_H
#define HUMAIN2_H

#include "joueur.h"

class Humain2 : public Joueur
{
public:
	Humain2(int numShip) : Joueur(numShip) {}
	virtual void demanderAction();
};

#endif