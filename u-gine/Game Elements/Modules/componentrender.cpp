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
	else if (msg->type == Message::MSGSSPRITESCALE) {
		MessageSetSpriteScale *msgScale = static_cast<MessageSetSpriteScale*>(msg);
		sprite->SetScale(msgScale->width / sprite->GetImage()->GetWidth(), msgScale->height / sprite->GetImage()->GetHeight());
		sprite->SetRadius((msgScale->height<msgScale->width ? msgScale->height / 2 : msgScale->width / 2));
	}
}
	
