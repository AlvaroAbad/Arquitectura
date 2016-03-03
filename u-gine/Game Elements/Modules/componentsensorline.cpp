#include "..\Headers\componentsensorline.h"
#include "../../include/math.h"

#include "../../include/renderer.h"

void ComponentSensorLine::Update(double elapsed)
{
	double originX, originY;
	MessageGetEntityState msgMyEntityState;
	MessageGetEntityState msgTriggererEntityState;
	owner->ReciveMessage(&msgMyEntityState);
	triggerer->ReciveMessage(&msgTriggererEntityState);
	originX = msgMyEntityState.o_x + msgMyEntityState.o_width*oX;
	originY = msgMyEntityState.o_y + msgMyEntityState.o_height*oY;
	switch (direction)
	{
	case ComponentSensorLine::HORIZONTAL:
		if (ValueInRange(originY, msgTriggererEntityState.o_y, msgTriggererEntityState.o_y + msgTriggererEntityState.o_height)) {
			MessageFire msgFire(msgTriggererEntityState.o_x, msgTriggererEntityState.o_y);
			owner->ReciveMessage(&msgFire);
		}
		
		break;
	case ComponentSensorLine::VERTICAL:
		if (ValueInRange(originX, msgTriggererEntityState.o_x, msgTriggererEntityState.o_x + msgTriggererEntityState.o_width)) {
			MessageFire msgFire(msgTriggererEntityState.o_x, msgTriggererEntityState.o_y);
			owner->ReciveMessage(&msgFire);
		}
		break;
	default:
		break;
	}
}

void ComponentSensorLine::ReciveMessage(Message * msg)
{
}
