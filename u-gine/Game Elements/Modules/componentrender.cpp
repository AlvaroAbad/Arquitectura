#include "..\Headers\componentrender.h"
#include "../../include/image.h"
void ComponentRender::Update(double elapsed)
{
	MessageGetEntityState getEntityState;
	owner->ReciveMessage(&getEntityState);
	sprite->SetPosition(getEntityState.o_x, getEntityState.o_y, getEntityState.o_z);
	sprite->SetAngle(getEntityState.o_rot);
	sprite->SetScale(getEntityState.o_width/sprite->GetImage()->GetWidth(), getEntityState.o_height/sprite->GetImage()->GetHeight());
	sprite->SetRadius((getEntityState.o_height>getEntityState.o_width ? getEntityState.o_height / 2 : getEntityState.o_width / 2));
	sprite->Update(elapsed);
}

void ComponentRender::ReciveMessage(Message * msg)
{
	if (msg->type == Message::MSGGSPRITE) {
		MessageGetSprite *msgGSprite = static_cast<MessageGetSprite *>(msg);
		msgGSprite->o_sprite = sprite;
	}
}
	
