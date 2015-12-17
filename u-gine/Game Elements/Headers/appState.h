#ifndef WORLDDEFENDER_APP_STATES_H
#define WORLDDEFENDER_APP_STATES_H
enum appStates {
	STATE_NULL,
	STATE_MENU,
	STATE_GAME,
	STATE_PAUSE
};
class AppState
{
public:
	
	virtual ~AppState() {};
	 void virtual run() =0;
	 void virtual draw() const = 0;
	 void virtual getInputs() = 0;
	 void virtual activate()  = 0;
	 void virtual deactivate() = 0;
	 void setState(appStates state) { this->state = state; }
	 appStates getState() const { return this->state; }
private:
	appStates state;
};
#endif
