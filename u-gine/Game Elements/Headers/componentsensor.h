#ifndef WORLDDEFENDERS_COMPONENT_SENSOR_H
#define WORLDDEFENDERS_COMPONENT_SENSOR_H
#include "component.h"
class ComponentSensor : public Component
{
public:
	ComponentSensor(double oX, double oY, Entity * triggerer):oX(oX), oY(oY), triggerer(triggerer){};
	virtual void Update(double elapsed)=0;
	virtual void ReciveMessage(Message * msg)=0;

protected:
	double oX, oY;
	Entity * triggerer;
};
#endif // !WORLDDEFENDERS_COMPONENT_SENSOR_H