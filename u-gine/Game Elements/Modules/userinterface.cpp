#include "..\Headers\userinterface.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#define G_KEY_W 87
#define G_KEY_A 65
#define G_KEY_D 68
#define G_KEY_S 83
#define FIRING_LIMIT 0.5
void UserInterface::run()
{
	world->setMousX(Screen::Instance().GetMouseX());
	world->setMousY(Screen::Instance().GetMouseY());
	if (Screen::Instance().KeyPressed(G_KEY_W)) {
		world->getPlayer()->jump();
	}
	if (Screen::Instance().KeyPressed(G_KEY_A)) {
		world->getPlayer()->setMovement(world->getPlayer()->LEFT);
	}
	else if (Screen::Instance().KeyPressed(G_KEY_D)) {
		world->getPlayer()->setMovement(world->getPlayer()->RIGHT);
	}
	else {
		world->getPlayer()->setMovement(world->getPlayer()->STOP);
	}
	if (Screen::Instance().KeyPressed(G_KEY_S) && !world->getPlayer()->isJumping()) {
		world->getPlayer()->setWidth(world->getPlayer()->getWidth() + world->getPlayer()->getRadius());
		world->getPlayer()->setHeight(world->getPlayer()->getHeight() - world->getPlayer()->getRadius());
	}
	if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && !world->getPlayer()->isFiring() && !world->getPlayer()->isOverheated()) {
		world->getPlayer()->setFiringLimit(FIRING_LIMIT);
	}
}
