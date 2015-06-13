#ifndef FOLOBALL_H
#define FOLOBALL_H

#include "balle.h"

class FoloBall : public Balle
{
public:
	FoloBall();
	virtual void calculVitesse();
};

#endif
