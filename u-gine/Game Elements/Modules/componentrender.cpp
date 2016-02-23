#include "..\Headers\componentrender.h"

void ComponentRender::ReciveMessage(Message * msg)
{
	switch (msg->type)
	{
	case Message::MSGMOVEMENT:
			sprite->SetPosition(0,0,0);
		break;
	default:
		break;
	}
}
