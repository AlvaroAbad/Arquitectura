#ifndef WORLDDEFENDERS_COMPONENT_ENTITYSTATE_H
#define WORLDDEFENDERS_COMPONENT_ENTITYSTATE_H
#include "component.h"
class ComponentEntityState: public Component
{
public:
	ComponentEntityState(double x, double y, double z, double rotation, double width, double height)
		:x(x), y(y), z(z), rotation(rotation), width(width), height(height) {};
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);

private:
	double x, y, z;
	double rotation;
	double width, height;
	double radious;
};
#endif // !WORLDDEFENDERS_COMPONENT_ENTITYSTATE_H
