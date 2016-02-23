#ifndef WORLDDEFENDER_ENTITY_H
#define WORLDDEFENDER_ENTITY_H
#include "component.h"
#include "message.h"
#include <vector>
class Entity {
public:
	void Update(double elapsed);
	void ReciveMessage(Message * msg);
	void AddComponent(Component * component);
private:
	std::vector<Component*> components;
};
#endif