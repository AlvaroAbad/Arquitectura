#ifndef UGINE_LISTENER_H
#define UGINE_LISTENER_H
#include "../lib/openal/AL/al.h"

class Listener {
public:
	static Listener& Instance();
	void SetPosition(float x, float y, float z) { alListener3f(AL_POSITION, x, y, z); }
	void SetVelocity(float x, float y, float z) { alListener3f(AL_VELOCITY, x, y, z); }
	void SetOrientation(float x, float y, float z) { alListener3f(AL_ORIENTATION, x, y, z); }
protected:
	Listener();
	~Listener() {}
private:
	static Listener* listener;
};
#endif