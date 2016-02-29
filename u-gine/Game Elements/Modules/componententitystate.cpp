#include "..\Headers\componententitystate.h"

void ComponentEntityState::Update(double elapsed)
{
}

void ComponentEntityState::ReciveMessage(Message * msg)
{
	switch (msg->type)
	{
	case Message::MSGSPOS:
	{
		MessageSetPos *msgMove = static_cast<MessageSetPos*>(msg);
		x = msgMove->x;
		y = msgMove->y;
		z = msgMove->z;
	}
		break;
	case  Message::MSGGETENTITYSTATE:
	{
		MessageGetEntityState *msgEntityState = static_cast<MessageGetEntityState*>(msg);
		msgEntityState->o_x = x;
		msgEntityState->o_y = y;
		msgEntityState->o_z = z;
		msgEntityState->o_rot = rotation;
		msgEntityState->o_width = width;
		msgEntityState->o_height = height;
	}
		break;
	case Message::MSGSROT:
	{
		MessageSetRotation *msgRotate = static_cast<MessageSetRotation*>(msg);
		rotation = msgRotate->rot;
	}
		break;
	case Message::MSGSSCALE:
	{
		MessageSetScale *msgScale = static_cast<MessageSetScale*>(msg);
		width = msgScale->width;
		height = msgScale->height;
	}
		break;
	default:
		break;
	}
}
