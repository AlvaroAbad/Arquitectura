#ifndef WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H
#define WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H

#include "component.h"

class ComponentPlayerControl: public Component
{
public:
	ComponentPlayerControl(double speedH, double speedV) : speedH(speedH), speedV(speedV) {};
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
private:
	double speedH, speedV;
	MessageMove::direction horizontal, vertical;
};
#endif // !WORLDDEFENDERS_COMPONENT_PLAYERCONTROL_H

