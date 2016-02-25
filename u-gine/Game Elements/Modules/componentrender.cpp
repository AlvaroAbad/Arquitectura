#include "..\Headers\componentrender.h"

void ComponentRender::Update(double elapsed)
{
	MessageGetEntityState getEntityState;
	owner->ReciveMessage(&getEntityState);
	sprite->SetPosition(getEntityState.o_x, getEntityState.o_y, getEntityState.o_z);
	sprite->SetAngle(getEntityState.o_rot);
	sprite->SetScale(getEntityState.o_sX, getEntityState.o_sY);
}

void ComponentRender::ReciveMessage(Message * msg)
{
}
	
