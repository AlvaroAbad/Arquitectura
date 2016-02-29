#include "..\Headers\componenttype.h"

void ComponentType::ReciveMessage(Message * msg)
{
	if (msg->type == Message::MSGGTYPE) {
		MessageGetEntityType * msgGEntityType = static_cast<MessageGetEntityType *>(msg);
		msgGEntityType->o_eType = eType;
	}
}
