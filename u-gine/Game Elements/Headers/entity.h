#ifndef WORLDDEFENDER_ENTITY_H
#define WORLDDEFENDER_ENTITY_H
#include "component.h"
#include <vector>
class Entity {
public:
	void Update(double elapsed);
	void AddComponent(Component * component);
private:
	std::vector<Component*> components;
};
#endif