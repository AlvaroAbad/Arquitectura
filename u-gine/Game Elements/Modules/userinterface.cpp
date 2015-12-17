#include "..\Headers\userinterface.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
void UserInterface::run()
{
	this->world->setMousX(Screen::Instance().GetMouseX());
	this->world->setMousY(Screen::Instance().GetMouseY());
	if (Screen::Instance().KeyPressed(87)) {
		this->world->getPlayer()->jump();
	}
	if (Screen::Instance().KeyPressed(65)) {
		this->world->getPlayer()->setMovement(this->world->getPlayer()->LEFT);
	}
	else if (Screen::Instance().KeyPressed(68)) {
		this->world->getPlayer()->setMovement(this->world->getPlayer()->RIGHT);
	}
	else {
		this->world->getPlayer()->setMovement(this->world->getPlayer()->STOP);
	}
	if (Screen::Instance().KeyPressed(83) && !this->world->getPlayer()->isJumping()) {
		this->world->getPlayer()->setWidth(this->world->getPlayer()->getWidth() + this->world->getPlayer()->getRadius());
		this->world->getPlayer()->setHeight(this->world->getPlayer()->getHeight() - this->world->getPlayer()->getRadius());
	}
	if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) && !this->world->getPlayer()->isFiring() && !this->world->getPlayer()->isOverheated()) {
		this->world->getPlayer()->setFiringLimit(1);
	}
	else {
		this->world->getPlayer()->setFiringLimit(0);
	}
}
