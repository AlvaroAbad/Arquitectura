#ifndef WORLDDEFENDER_APP_STATE_MENU_H
#define WORLDDEFENDER_APP_STATE_MENU_H
#include "appState.h"
#include "../../include/font.h"
#include "../../include/emitter.h"
#pragma warning(disable:4820)
class AppStateMenu : public AppState
{
public:
	AppStateMenu() {
		this->setState(STATE_MENU);
		font = nullptr;
		selectedOption = 0;
		screen = 0;
	}
	virtual ~AppStateMenu() {};
	void virtual run();
	void virtual draw() const;
	void virtual getInputs();
	void virtual activate();
	void virtual deactivate();
private:
	Array<String> options;
	Font *font;
	Image *selectorImage;
	Emitter * escapePoint;
	uint32 x, y, selectedOption, screen;
	int32 lasPressed;
	bool ready;
};

#endif