#include "..\Headers\componentcollision.h"
#include "../../include/collision.h"
#include "../../include/math.h"
void ComponentCollision::Update(double elapsed)
{
	if (didCollide) {
		MessageGetEntityType msgGEntityTypeMe;
		owner->ReciveMessage(&msgGEntityTypeMe);
		switch (msgGEntityTypeMe.o_eType)
		{
		case ETPLAYER:
			if (collidedType == ETEBULLET) {
				deadEnemies->Add(owner);
			}
			else if (collidedType == ETCOLLISIONER) {
				MessageGetEntityState msgGEnityState;
				owner->ReciveMessage(&msgGEnityState);
				MessageSetScale msgSScale(msgGEnityState.o_width + 10, msgGEnityState.o_height + 10);
				owner->ReciveMessage(&msgSScale);
				didCollide = false;
			}
			break;
		default:
			if (collidedType == ETPLAYER) {
				deadEnemies->Add(owner);
			}
			else if (collidedType == ETLASER && msgGEntityTypeMe.o_eType == ETSHOOTER) {
				deadEnemies->Add(owner);
			}
			break;
		}
	}

}

void ComponentCollision::ReciveMessage(Message * msg)
{

	switch (msg->type)
	{
	case Message::MSGCCOL:
	{
		if (!didCollide) {
			MessageGetCollider msgGCollision;
			MessageCheckCollision * msgCCollision = static_cast<MessageCheckCollision *>(msg);
			msgCCollision->entity->ReciveMessage(&msgGCollision);
			didCollide = collider->DoesCollide(msgGCollision.o_collision);
			if (didCollide) {
				MessageGetEntityType msgGEntityTypeOther;
				MessageSetCollision msgSCollision(owner);
				collision = msgCCollision->entity;
				collision->ReciveMessage(&msgGEntityTypeOther);
				collidedType = msgGEntityTypeOther.o_eType;
				msgCCollision->entity->ReciveMessage(&msgSCollision);
			}
		}
	}
	break;
	case Message::MSGGCOL:
	{
		MessageGetCollider * msgGCollision = static_cast<MessageGetCollider *>(msg);
		msgGCollision->o_collision = collider;
	}
	break;
	case Message::MSGSCOL:
	{
		MessageSetCollision * msgSCollision = static_cast<MessageSetCollision *>(msg);
		MessageGetEntityType msgGEntityTypeOther;
		collision = msgSCollision->entity;
		collision->ReciveMessage(&msgGEntityTypeOther);
		collidedType = msgGEntityTypeOther.o_eType;
		didCollide = true;
	}
	break;
	case Message::MSGCFIRECOL:
	{
		MessageCheckFireCollision * msgCFireCollision = static_cast<MessageCheckFireCollision *>(msg);
		MessageGetEntityState msgGEntityState;
		owner->ReciveMessage(&msgGEntityState);
		uint32 tlAngle, brAngle, trAngle, blAngle, lineAngle;
		tlAngle = Angle(msgGEntityState.o_x, msgGEntityState.o_y, msgCFireCollision->originX, msgCFireCollision->originY);
		brAngle = Angle(msgGEntityState.o_x + msgGEntityState.o_width, msgGEntityState.o_y + msgGEntityState.o_height, msgCFireCollision->originX, msgCFireCollision->originY);
		trAngle = Angle(msgGEntityState.o_x + msgGEntityState.o_width, msgGEntityState.o_y, msgCFireCollision->originX, msgCFireCollision->originY);
		blAngle = Angle(msgGEntityState.o_x, msgGEntityState.o_y + msgGEntityState.o_height, msgCFireCollision->originX, msgCFireCollision->originY);
		lineAngle = Angle(msgCFireCollision->targetX, msgCFireCollision->targetY, msgCFireCollision->originX, msgCFireCollision->originY);
		if ((blAngle >= lineAngle && trAngle <= lineAngle)
			|| (tlAngle >= lineAngle && brAngle <= lineAngle)) {
			didCollide = true;
			collidedType = ETLASER;
		}
	}
	break;
	}
}
