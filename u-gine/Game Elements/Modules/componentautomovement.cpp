#include "..\Headers\componentautomovement.h"

void ComponentAutomaticMovement::SetBoundaries(double topLeftBoundariesX, double topLeftBoundariesY, double botRightBoundariesX, double botRightBoundariesY)
{
	this->topLeftBoundariesX = topLeftBoundariesX;
	this->topLeftBoundariesY = topLeftBoundariesY;
	this->botRightBoundariesX = botRightBoundariesX;
	this->botRightBoundariesY = botRightBoundariesY;
}

void ComponentAutomaticMovement::Update(double elapsed)
{
	MessageGetEntityState msgEntityState;
	owner->ReciveMessage(&msgEntityState);
	msgEntityState.o_x += speedH*elapsed;
	msgEntityState.o_y += speedV*elapsed;
	if (msgEntityState.o_x < topLeftBoundariesX || msgEntityState.o_x > botRightBoundariesX) {
		if (destroyOnExit) {

		}
		else {
			msgEntityState.o_x = (msgEntityState.o_x < topLeftBoundariesX ? topLeftBoundariesX : botRightBoundariesX);
			speedH = speedH*-1;
		}
	}
	if (msgEntityState.o_y < topLeftBoundariesY || msgEntityState.o_y > botRightBoundariesY) {
		if (destroyOnExit) {

		}
		else{
			msgEntityState.o_y = (msgEntityState.o_y < topLeftBoundariesY ? topLeftBoundariesX : botRightBoundariesY);
			speedV = speedV*-1;
		}
	}
	MessageSetPos msgSPos(msgEntityState.o_x, msgEntityState.o_y, 0);
	owner->ReciveMessage(&msgSPos);
}

void ComponentAutomaticMovement::ReciveMessage(Message * msg)
{
}
