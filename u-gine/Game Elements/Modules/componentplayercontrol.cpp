#include "..\Headers\componentplayercontrol.h"
#include "../../include/screen.h"
void ComponentPlayerControl::Update(double elapsed)
{
	MessageGetEntityState msgEntityState;
	owner->ReciveMessage(&msgEntityState);
	if(originalWidth && originalHeight){
	msgEntityState.o_width =originalWidth;
	msgEntityState.o_height=originalHeight;
	}
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
		if (!isFalling) {
			isJumping = true;
		}
		break;
	case MessageMove::DIRDOWN:
		originalWidth = msgEntityState.o_width;
		originalHeight= msgEntityState.o_height;
		msgEntityState.o_height = msgEntityState.o_height*0.5;
		msgEntityState.o_width = msgEntityState.o_width*1.5;
		break;
	}
	if (msgEntityState.o_y <= Screen::Instance().GetHeight() - (1.5 * msgEntityState.o_height) && isJumping) {
		isJumping = false;
		isFalling = true;
	}
	else if (msgEntityState.o_y >= Screen::Instance().GetHeight() && isFalling) {
		isJumping = false;
		isFalling = false;
		msgEntityState.o_y = Screen::Instance().GetHeight();
	}
	else if (isJumping) {
		msgEntityState.o_y -= (4*msgEntityState.o_height)*Screen::Instance().ElapsedTime();
	}
	else if (isFalling) {
		msgEntityState.o_y += (4*msgEntityState.o_height)*Screen::Instance().ElapsedTime();
	}
	MessageSetPos msgSetPos(msgEntityState.o_x, msgEntityState.o_y,0);
	MessageSetScale msgSetScale(msgEntityState.o_width, msgEntityState.o_height);
	owner->ReciveMessage(&msgSetPos);
	owner->ReciveMessage(&msgSetScale);

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
