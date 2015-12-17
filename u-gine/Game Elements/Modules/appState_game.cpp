#include "../Headers/appState_game.h"
#include "../../include/screen.h"
#include "../../include/glinclude.h"
#include "../Headers/externs.h"
void AppStateGame::run()
{
	game->run();
}

void AppStateGame::draw() const
{
	game->draw();
}

void AppStateGame::getInputs() const
{
	game->getInput();
	if (Screen::Instance().KeyPressed(GLFW_KEY_ESC) || game->isEndGame()) {
		whantedState = STATE_MENU;
	}
	else if (Screen::Instance().KeyPressed(GLFW_KEY_SPACE)) {
		whantedState = STATE_PAUSE;
	}
}

void AppStateGame::activate()
{
	if (!game) {
		game = new Game();
		game->initialize();
	}

}

void AppStateGame::deactivate()
{

}
