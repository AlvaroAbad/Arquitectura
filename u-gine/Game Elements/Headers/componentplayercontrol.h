#ifndef WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H
#define WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H

#include "component.h"

class ComponentPlayerControl: public Component
{
public:
	ComponentPlayerControl(double speedH, double speedV) : speedH(speedH), speedV(speedV),isJumping(false), isFalling(false), originalWidth(0), originalHeight(0) {
};
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
private:
	double speedH, speedV;
	double originalWidth, originalHeight;
	bool isJumping, isFalling;
	MessageMove::direction horizontal, vertical;
};
#endif // !WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H

