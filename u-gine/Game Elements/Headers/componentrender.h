#ifndef WORLDDEFENDER_COMPONENTRENDER_H
#define WORLDDEFENDER_COMPONENTRENDER_H
#include "component.h"
class ComponentRender: public Component
{
public:
	virtual void Update(double elapsed);
	//virtual void ReciveMessage(Message msg);
private:
	Entity * owner;
};
#endif // !WORLDDEFENDER_COMPONENTRENDER_H