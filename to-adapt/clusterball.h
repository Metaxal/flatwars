#ifndef CLUSTERBALL_H
#define CLUSTERBALL_H

#include "balle.h"

class ClusterBall : public Balle
{
private:
	int _timer;
public:
	ClusterBall();
	virtual void exploseMur(int xc, int yc);
	virtual void calculVitesse();
};

#endif
