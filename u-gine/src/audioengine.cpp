#include "..\include\audioengine.h"
#include "../lib/openal/AL/al.h"
#include "../lib/openal/AL/alc.h"
AudioEngine*AudioEngine::engine;
AudioEngine & AudioEngine::Instance()
{
	if (!engine) {
		engine = new AudioEngine();
	}
	return *engine;
}

void AudioEngine::Init()
{
	device=alcOpenDevice(nullptr);
	context=alcCreateContext((ALCdevice*)device, nullptr);
	alcMakeContextCurrent((ALCcontext*)context);
}

void AudioEngine::Finish()
{
	alcDestroyContext((ALCcontext*)context);
	alcCloseDevice((ALCdevice*)device);
}

void AudioEngine::SetDopplerFactor(float factor) {
	alDopplerFactor(factor);
}
