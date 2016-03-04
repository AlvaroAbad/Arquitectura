#include "../Headers/appState.h"
#include "../Headers/appState_menu.h"
#include "../Headers/appState_game.h"
#include "../Headers/appState_pause.h"
#include "../../include/screen.h"
#include "../../include/renderer.h"
#include "../../include/resourcemanager.h"
#include "../Headers/languagemanager.h"
#include "../Headers/game.h"
AppState *currentState = nullptr;
appStates whantedState = STATE_MENU;
Game *game = nullptr;
AppState * newAppState(appStates state) {
	switch (state)
	{
	case STATE_MENU:
		return new AppStateMenu();
		break;
	case STATE_GAME:
		return new AppStateGame();
		break;
	case STATE_PAUSE:
		return new AppStatePause();
	case STATE_NULL:		
	default:
		return nullptr;
		break;
	}
}
int main(int, char*) {
	Screen::Instance().Open(800, 600, false);
	while (whantedState) {
			if (!currentState || currentState->getState() != whantedState) {
				if (currentState) {
					currentState->deactivate();
					delete(currentState);
				}
				currentState = newAppState(whantedState);
				currentState->activate();
			}
			currentState->run();
			currentState->draw();
			currentState->getInputs();
			Screen::Instance().Refresh();
			Renderer::Instance().Clear(0, 0, 0);
		}
	ResourceManager::Instance().FreeResources();
}