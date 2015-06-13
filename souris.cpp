#include "souris.h"

bool souris[NB_BUTTONS];
int souris_xmax;
int souris_ymax;
int souris_zaxis;

void initSouris(int xmax, int ymax)
{
    souris_xmax = xmax;
    souris_ymax = ymax;
    souris_zaxis = 0;

    initBoutons(false);
}

void initBoutons(bool b)
{
    for(int i=0; i < NB_BUTTONS; i++)
        souris[i] = b;
}

int souris_getZAxis()
{
    int z = souris_zaxis;
    souris_zaxis = 0;
    return z;
}


void finSouris()
{
}
