#ifndef FOLOBULLETS_H
#define FOLOBULLETS_H

#include "bullets.h"

#define INC_FOLOBULLETS		14

class FoloBullets : public Bullets
{
public:
	FoloBullets();
	virtual bool bonusAgir(Joueur *j);
};

#endif
