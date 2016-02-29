#include "..\Headers\entity.h"
#include "../Headers/component.h"
void Entity::Update(double elapsed)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->Update(elapsed);
	}
}

void Entity::ReciveMessage(Message * msg)
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		components[i]->ReciveMessage(msg);
	}
}

void Entity::AddComponent(Component * component)
{
	component->setOwner(this);
	components.push_back(component);
}

Entity::~Entity()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
}
