#include "..\Headers\componententitystate.h"

void ComponentEntityState::Update(double elapsed)
{
}

void ComponentEntityState::ReciveMessage(Message * msg)
{
	switch (msg->type)
	{
	case Message::MSGMOVE:
		MessageMove *msgMove = static_cast<MessageMove*>(msg);
		x = msgMove->x;
		y = msgMove->y;
		z = msgMove->z;
		break;
	case  Message::MSGGETENTITYSTATE:
		MessageGetEntityState *msgEntityState = static_cast<MessageGetEntityState*>(msg);
		msgEntityState->o_x = x;
		msgEntityState->o_y = y;
		msgEntityState->o_z = z;
		msgEntityState->o_rot = rotatioin;
		msgEntityState->o_sX = scaleX;
		msgEntityState->o_sY= scaleY;
		break;
	case Message::MSGROTATE:
		MessageRotate *msgRotate = static_cast<MessageRotate*>(msg);
		rotatioin = msgRotate->rot;
		break;
	case Message::MSGSCALE:
		MessageScale *msgScale = static_cast<MessageScale*>(msg);
		scaleX = msgScale->scaleX;
		scaleY = msgScale->scaleY;
		break;
	default:
		break;
	}
}
