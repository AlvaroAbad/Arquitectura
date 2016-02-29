#include "..\Headers\userinterface.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../../Game Elements/Headers/message.h"

#define G_KEY_W 87
#define G_KEY_A 65
#define G_KEY_D 68
#define G_KEY_S 83
#define FIRING_LIMIT 0.5
void UserInterface::run()
{
	world->setMousX(Screen::Instance().GetMouseX());
	world->setMousY(Screen::Instance().GetMouseY());
	MessageMove msgMove;
	MessageFire msgFire(Screen::Instance().GetMouseX(), Screen::Instance().GetMouseY());
	MessageMove::direction horizontal, vertical;
	horizontal = MessageMove::DIRNULL;
	vertical = MessageMove::DIRNULL;
	if (Screen::Instance().KeyPressed(G_KEY_W)) {
		vertical = MessageMove::DIRUP;
	}
	else if (Screen::Instance().KeyPressed(G_KEY_S)) {
		vertical = MessageMove::DIRDOWN;
	}

	if (Screen::Instance().KeyPressed(G_KEY_A)) {
		horizontal = MessageMove::DIRLEFT;
	}
	else if (Screen::Instance().KeyPressed(G_KEY_D)) {
			horizontal = MessageMove::DIRRIGHT;
	}
	msgMove.Horizontal = horizontal;
	msgMove.Vertical = vertical;
	world->getPlayer()->ReciveMessage(&msgMove);
	if (Screen::Instance().MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		world->getPlayer()->ReciveMessage(&msgFire);
	}
}
