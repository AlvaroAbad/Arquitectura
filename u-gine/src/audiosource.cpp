#include "..\include\audiosource.h"
#include "..\include\audiostream.h"
AudioSource::AudioSource(AudioBuffer * buffer)
{
	alGenSources(1, &source);
	stream = NULL;
	alSourcef(source, AL_PITCH, 1.0);
	alSourcef(source, AL_GAIN, 1.0);
	alSource3f(source, AL_POSITION, 0.0, 0.0, 0.0);
	alSource3f(source, AL_VELOCITY, 0.0, 0.0, 0.0);
	alSourcef(source, AL_LOOPING, false);
	alSourcef(source, AL_BUFFER, buffer->GetBuffer());
}

AudioSource::AudioSource(const String & filename)
{
	alGenSources(1, &source);
	stream = new AudioStream(filename, this);
	alSourcef(source, AL_PITCH, 1.0);
	alSourcef(source, AL_GAIN, 1.0);
	alSource3f(source, AL_POSITION, 0.0, 0.0, 0.0);
	alSource3f(source, AL_VELOCITY, 0.0, 0.0, 0.0);
	alSourcef(source, AL_LOOPING, false);
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &source);
}

void AudioSource::SetLooping(bool loop)
{
	if (stream) {
		stream->SetLooping(loop);
	}
	else {
		 alSourcef(source, AL_LOOPING, loop);
	}
}

bool AudioSource::IsPlaying() const
{
	int32 value;
	alGetSourcei(source, AL_SOURCE_STATE, &value);
	return value== AL_PLAYING;
}
