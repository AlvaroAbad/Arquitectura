#ifndef WORLDDEFENDERS_COMPONENT_SENSOR_LINE_H
#define WORLDDEFENDERS_COMPONENT_SENSOR_LINE_H
#include "componentsensor.h"
class ComponentSensorLine : public ComponentSensor
{
public:
	enum LineDirection {
		HORIZONTAL,
		VERTICAL
	};
	ComponentSensorLine(double oX, double oY,Entity * triggerer, LineDirection direction, double length) :ComponentSensor(oX,oY, triggerer), direction(direction), length(length){};
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);

private:
	LineDirection direction;
	double length;
};
#endif // !WORLDDEFENDERS_COMPONENT_SENSOR_RECT_H
