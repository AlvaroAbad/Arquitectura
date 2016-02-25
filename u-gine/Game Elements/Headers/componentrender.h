#ifndef WORLDDEFENDER_COMPONENTRENDER_H
#define WORLDDEFENDER_COMPONENTRENDER_H
#include "component.h"
#include "../../include/sprite.h"

class ComponentRender: public Component
{
public:
	ComponentRender(Sprite * sprite) : sprite(sprite) {}
	virtual void Update(double elapsed);
	virtual void ReciveMessage(Message * msg);
private:
	Entity * owner;
	Sprite * sprite;
};
#endif // !WORLDDEFENDER_COMPONENTRENDER_H
