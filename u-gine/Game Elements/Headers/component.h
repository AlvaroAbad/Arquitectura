#ifndef WORLDDEFENDER_COMPONENT_H
#define WORLDDEFENDER_COMPONENT_H
#include "entity.h"
class Component
{
public:
	virtual void Update(double elapsed) = 0;
	//virtual void ReciveMessage(Message msg)=0;
private:
	Entity * owner;
};
#endif // !WORLDDEFENDER_COMPONENT_H
