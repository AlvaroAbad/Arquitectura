#include "..\Headers\componentplayercontrol.h"
#include "../../include/screen.h"
void ComponentPlayerControl::Update(double elapsed)
{
	MessageGetEntityState msgEntityState;
	owner->ReciveMessage(&msgEntityState);
	switch (horizontal)
	{
	case MessageMove::DIRLEFT:
		msgEntityState.o_x -= speedH*elapsed;
		if (msgEntityState.o_x < 0) {
			msgEntityState.o_x = 0;
		}
		break;
	case MessageMove::DIRRIGHT:
		msgEntityState.o_x += speedH*elapsed;
		if (msgEntityState.o_x > Screen::Instance().GetWidth()) {
			msgEntityState.o_x = Screen::Instance().GetWidth();
		}
		break;
	}
	switch (vertical)
	{
	case MessageMove::DIRUP:
		msgEntityState.o_y -= speedV*elapsed;
		if (msgEntityState.o_y < 0) {
			msgEntityState.o_y = 0;
		}
		break;
	case MessageMove::DIRDOWN:
		msgEntityState.o_y += speedV*elapsed;
		if (msgEntityState.o_y > Screen::Instance().GetHeight()) {
			msgEntityState.o_y = Screen::Instance().GetHeight();
		}
		break;
	}
	MessageSetPos msgSetPos(msgEntityState.o_x, msgEntityState.o_y,0);
	owner->ReciveMessage(&msgSetPos);

}

void ComponentPlayerControl::ReciveMessage(Message * msg)
{
	switch (msg->type)
	{
	case Message::MSGMOVE:
	{
		MessageMove *msgMove = static_cast<MessageMove*>(msg);
		horizontal = msgMove->Horizontal;
		vertical = msgMove->Vertical;
	}
	}
}
