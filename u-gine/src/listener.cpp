#include "..\include\listener.h"

Listener*Listener::listener;
Listener & Listener::Instance()
{
	if (!listener) {
		listener = new Listener();
	}
	return *listener;
}

Listener::Listener()
{
	alListener3f(AL_POSITION, 0, 0, 0);	alListener3f(AL_ORIENTATION, 0, 0, 0);	alListener3f(AL_VELOCITY, 0, 0, 0);
}
