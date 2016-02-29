#ifndef WORLDDEFENDERS_COMPONENT_COLLISION_H
#define WORLDDEFENDERS_COMPONENT_COLLISION_H

#include "component.h"
#include "../../include/array.h"
class ComponentCollision: public Component
{
public:
	ComponentCollision(const Collision * collider, Array<Entity*> *deadEnemies):collider(collider), deadEnemies(deadEnemies){
		collision = nullptr;
		didCollide = false;
	};
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
private:
	Entity * collision;
	EntityType collidedType;
	bool didCollide;
	const Collision * collider;
	Array<Entity*> *deadEnemies;
};
#endif // !WORLDDEFENDERS_COMPONENT_COLLISION_H
