#include "humain2.h"
#include "..\\utils\\clavier.h"
#include "..\\utils\\souris.h"

void Humain2::demanderAction()
{
	action = 0;

	bool bg = false, bd = false;
//	int ax, ay;

	//sourisGetXY(ax, ay, bg, bd);
	tourner((rand()*9)/RAND_MAX-4);

	if(bg)
		action |= FIRE1;
	if(bd)
		action |= FIRE2;

	DIGetKeys();
	if(DIKeyPressed(KFr_Z) || DIKeyPressed(DIK_UP))
		action |= FORWARD;
	if(DIKeyPressed(KFr_S) || DIKeyPressed(DIK_DOWN))
		action |= BACKWARD;
	if(DIKeyPressed(KFr_Q))
		action |= STRAFE_LEFT;
	if(DIKeyPressed(KFr_D))
		action |= STRAFE_RIGHT;
	if(DIKeyPressed(DIK_LEFT))
		action |= TURN_LEFT;
	if(DIKeyPressed(DIK_RIGHT))
		action |= TURN_RIGHT;
	if(DIKeyPressed(DIK_RCONTROL))
		action |= FIRE1;
	else if(DIKeyPressed(DIK_NUMPAD0))
		action |= FIRE2;

}