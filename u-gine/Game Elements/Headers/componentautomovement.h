#ifndef WORLDDEFENDERS_COMPONENT_AUTOMOVEMENT_H
#define WORLDDEFENDERS_COMPONENT_AUTOMOVEMENT_H

#include "component.h"

class ComponentAutomaticMovement : public Component
{
public:

	ComponentAutomaticMovement(double speedH, double speedV, bool destroyOnExit) 
		: speedH(speedH), speedV(speedV), destroyOnExit(destroyOnExit){};
	virtual void SetBoundaries(double topLeftBoundariesX, double topLeftBoundariesY,
		double botRightBoundariesX, double botRightBoundariesY);
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
private:
	double speedH, speedV;
	double topLeftBoundariesX, topLeftBoundariesY;
	double botRightBoundariesX, botRightBoundariesY;
	bool destroyOnExit;
};
#endif // !WORLDDEFENDERS_COMPONENT_AUTOMOVEMENT_H
