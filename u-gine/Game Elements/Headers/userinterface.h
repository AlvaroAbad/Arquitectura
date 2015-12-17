#ifndef WORLDDEFENDER_USERINTERFACE_H
#define WORLDDEFENDER_USERINTERFACE_H
#include "world.h"
class UserInterface
{
public:
	UserInterface(World * world) { this->world = world; };
	void userInterfaceInit() {}
	~UserInterface() {};
	World * getWorld() { return this->world; }
	void run();

private:
	World *world;
};
#endif