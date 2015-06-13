#ifndef SOURIS_H
#define SOURIS_H

#define NB_BUTTONS 10

//class myMouse
//{
//protected:
//    bool _buttons[];
//
//public:
//    myMouse();
//
//    int button(int b);
//    int getZAxis();
//};

extern bool souris[NB_BUTTONS];
extern int souris_xmax;
extern int souris_ymax;
extern int souris_zaxis;

void initSouris(int xmax, int ymax);
void initBoutons(bool b=false);
int souris_getZAxis();
void finSouris();


#endif
