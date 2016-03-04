#ifndef WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H
#define WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H

#include "component.h"

class ComponentPlayerControl: public Component
{
public:
	ComponentPlayerControl(double speedH, double speedV) : speedH(speedH), speedV(speedV),isJumping(false), isFalling(false) {
};
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
private:
	double speedH, speedV;
	bool isJumping, isFalling;
	MessageMove::direction horizontal, vertical;
};
#endif // !WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H

