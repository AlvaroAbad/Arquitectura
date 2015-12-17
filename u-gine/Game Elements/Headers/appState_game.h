#ifndef WORLDDEFENDER_APP_STATE_GAME_H
#define WORLDDEFENDER_APP_STATE_GAME_H
#include "appState.h";
#include "../../include/font.h";
class AppStateGame : public AppState
{
public:
	AppStateGame() {
		this->setState(STATE_GAME);
	}
	virtual ~AppStateGame() {};
	void virtual run();
	void virtual draw() const;
	void virtual getInputs() const;
	void virtual activate();
	void virtual deactivate();
private:
};

#endif