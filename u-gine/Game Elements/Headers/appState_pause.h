#ifndef WORLDDEFENDER_APP_STATE_PAUSE_H
#define WORLDDEFENDER_APP_STATE_PAUSE_H
#include "appState.h";
#include "../../include/font.h";
class AppStatePause : public AppState
{
public:
	AppStatePause() {
		this->setState(STATE_PAUSE);
		font = nullptr;
		selectedOption = 0;
	}
	virtual ~AppStatePause() {};
	void virtual run();
	void virtual draw() const;
	void virtual getInputs();
	void virtual activate();
	void virtual deactivate();
private:
	Array<String> options;
	Font *font;
	Image *selectorImage;
	uint32 x, y, selectedOption;
};

#endif