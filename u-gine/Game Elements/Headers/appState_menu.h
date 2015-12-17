#ifndef WORLDDEFENDER_APP_STATE_MENU_H
#define WORLDDEFENDER_APP_STATE_MENU_H
#include "appState.h";
#include "../../include/font.h";
class AppStateMenu : public AppState
{
public:
	AppStateMenu() {
		this->setState(STATE_MENU);
		font = nullptr;
	}
	virtual ~AppStateMenu() {};
	void virtual run();
	void virtual draw() const;
	void virtual getInputs() const;
	void virtual activate();
	void virtual deactivate();
private:
	Array<String> options;
	Font *font;
	uint32 x, y;
};

#endif