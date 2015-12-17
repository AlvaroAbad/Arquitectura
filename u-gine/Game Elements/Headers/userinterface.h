#ifndef WORLDDEFENDER_USERINTERFACE_H
#define WORLDDEFENDER_USERINTERFACE_H
#include "world.h"
class UserInterface
{
public:
	UserInterface() { this->world = nullptr; };
	void userInterfaceInit() {
		world = new World();
		world->worldInit();
	}
	~UserInterface() { delete this->world; };
	World * getWorld() { return this->world; }
	void run();

private:
	World *world;
};
#endif