#include "..\Headers\componentfire.h"
#include "../../include/math.h"
void ComponentFire::Update(double elapsed)
{

	if (fire) {
		MessageGetEntityState msgEntityState;
		owner->ReciveMessage(&msgEntityState);
		if (fireImage) {
			if (!remeiningCD) {
				world->CreateBullet(fireImage, msgEntityState.o_x+ msgEntityState.o_width/2, msgEntityState.o_y+ msgEntityState.o_height, targetX, targetY);
				fire = false;
				remeiningCD = cooldown;
			}
		}
		else if (true) {
			double angle = Angle(msgEntityState.o_x, msgEntityState.o_y, targetX, targetY);
			originX = msgEntityState.o_x + (angle < 62 ? msgEntityState.o_width / 2 : angle>118 ? -msgEntityState.o_width / 2 : msgEntityState.o_height / DegTan(angle));
			originY = msgEntityState.o_y - (angle > 62 && angle < 118 ? msgEntityState.o_height : abs((msgEntityState.o_width / 2) * DegTan(angle)));

			remeiningCD += elapsed;
			MessageCheckFireCollision msgFireCollision(originX, originY, targetX, targetY);
			for (size_t i = 0; i < world->GetEntities()->Size(); i++)
			{
				if (owner != (*world->GetEntities())[i]) {
					(*world->GetEntities())[i]->ReciveMessage(&msgFireCollision);
				}
			}
		}
		else {
			fire = false;
			heated = true;
		}
	}
	else if (remeiningCD > 0) {
		remeiningCD -= elapsed;
		if (remeiningCD <= 0) {
			remeiningCD = 0;
			heated = false;
		}
	}
}

void ComponentFire::ReciveMessage(Message * msg)
{
	switch (msg->type)
	{
	case Message::MSGFIRE:
	{
		MessageFire * msgFire = static_cast<MessageFire*>(msg);
		fire = true;
		targetX = msgFire->targetX;
		targetY = msgFire->targetY;
	}
	break;
	case Message::MSGGFIREVECTOR:
	{
		MessageGetFiringVector * msgFire = static_cast<MessageGetFiringVector*>(msg);
		msgFire->o_firing = fire;
		msgFire->o_originX = originX;
		msgFire->o_originY = originY;
		msgFire->o_targetX = targetX;
		msgFire->o_targetY = targetY;
		fire = false;
	}
	break;
	}
}

bool ComponentFire::rayRectColision(double rX, double rY, double rWidth, double rHeight, double oX, double oY, double dX, double dY)

{
	uint32 tlAngle, brAngle, lineAngle;
	tlAngle = Angle(rX, rY, oX, oY);
	brAngle = Angle(rX + rWidth, rY + rHeight, oX, oY);
	lineAngle = Angle(dX, dY, oX, oY);
	return lineAngle <= tlAngle &&  lineAngle >= brAngle;
}

int32 ComponentFire::closestRectToPoint(double oX, double oY, double r1X, double r1Y, double r1Width, double r1Height, double r2X, double r2Y, double r2Width, double r2Height)
{
	uint32 ret;
	double distance[8] = {
		Distance(oX, oY, r1X, r1Y),
		Distance(oX, oY, r1X + r1Width, r1Y),
		Distance(oX, oY, r1X, r1Y + r1Height),
		Distance(oX, oY, r1X, r1Y + r1Height),
		Distance(oX, oY, r2X, r2Y),
		Distance(oX, oY, r2X + r2Width, r2Y),
		Distance(oX, oY, r2X, r2Y + r2Height),
		Distance(oX, oY, r2X + r2Width, r2Y + r2Height)
	};
	ret = 0;
	for (size_t i = 1; i < 8; i++) {
		if (distance[ret] > distance[i]) {
			ret = i;
		}
	}
	if (ret > 3) {
		return -1;
	}
	else {
		return 1;
	}
}
