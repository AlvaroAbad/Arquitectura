#ifndef WORLDDEFENDERS_COMPONENT_TYPE_H
#define WORLDDEFENDERS_COMPONENT_TYPE_H

#include "component.h"
#include "enumentitytype.h"

class ComponentType: public Component
{
public:
	ComponentType(EntityType eType)
		: eType(eType){};
	virtual void Update(double elapsed) {};
	virtual void ReciveMessage(Message * msg);
private:
	EntityType eType;
};
#endif // !WORLDDEFENDERS_COMPONENT_TYPE_H
