#ifndef UGINE_AUDIOSOURCE_H
#define UGINE_AUDIOSOURCE_H
#include "audiobuffer.h"
#include "../lib/openal/AL/al.h"
class AudioStream;

class AudioSource {
public:
	AudioSource(AudioBuffer* buffer);
	AudioSource(const String& filename);
	~AudioSource();
	void SetPitch(float pitch) { alSourcef(source, AL_PITCH, pitch); }
	void SetGain(float gain) { alSourcef(source, AL_GAIN, gain); }
	void SetLooping(bool loop);
	void SetPosition(float x, float y, float z) { alSource3f(source, AL_POSITION, x, y, z); }
	void SetVelocity(float x, float y, float z) { alSource3f(source, AL_VELOCITY, x, y, z); }
	void Play() { alSourcePlay(source); }
	void Stop() { alSourceStop(source); }
	void Pause() { alSourcePause(source); }
	unsigned int GetSource() { return source; }
	bool IsPlaying() const;
private:
	unsigned int source;
	AudioStream* stream;
};
#endif