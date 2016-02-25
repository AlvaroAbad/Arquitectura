#ifndef WORLDDEFENDERS_COMPONENT_ENTITYSTATE_H
#define WORLDDEFENDERS_COMPONENT_ENTITYSTATE_H
#include "component.h"
class ComponentEntityState: public Component
{
public:
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);

private:
	double x, y, z;
	double rotatioin;
	double scaleX, scaleY;
};
#endif // !WORLDDEFENDERS_COMPONENT_ENTITYSTATE_H

