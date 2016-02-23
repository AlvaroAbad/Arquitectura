#include "audiostream.h"
#include "../lib/openal/AL/al.h"
#include "../include/audiosource.h"
Array<AudioStream*> AudioStream::streams;
AudioStream::AudioStream(const String & filename, AudioSource * source)
{
	shouldLoop = false;
	this->source = source;
	stream = stb_vorbis_open_filename(filename.ToCString(), NULL, NULL);
	info = stb_vorbis_get_info(stream);
	samplesLeft = stb_vorbis_stream_length_in_samples(stream)*info.channels;
	alGenBuffers(2, buffers);
	Stream(buffers[0]);
	Stream(buffers[1]);
	alSourceQueueBuffers(source->GetSource(), 2, buffers);
	streams.Add(this);
}

AudioStream::~AudioStream()
{
	alDeleteBuffers(2, buffers);
	AudioStream * aux = this;
	streams.Remove(aux);
}

void AudioStream::UpdateAll()
{
	for (uint32 i = 0; i < streams.Size(); i++)
	{
		streams[i]->Update();
	}
}

void AudioStream::Update()
{
	int32 value;
	uint32 unquedId;
	alGetSourcei(source->GetSource(), AL_BUFFERS_PROCESSED, &value);
	for (int32 i = 0; i < value; i++)
	{
		alSourceUnqueueBuffers(source->GetSource(), 1, &unquedId);
		if (Stream(unquedId)) {
			alSourceQueueBuffers(source->GetSource(), 1, &unquedId);
		}
		else if (shouldLoop) {
			stb_vorbis_seek_start(stream);
			samplesLeft = stb_vorbis_stream_length_in_samples(stream)*info.channels;
			if (Stream(unquedId)) {
				alSourceQueueBuffers(source->GetSource(), 1, &unquedId);
			}
		}

	}
}

bool AudioStream::Stream(unsigned int buffer)
{
	int16 pcm[32768];
	uint32 bytesRead;
	ALenum format;
	bytesRead=stb_vorbis_get_samples_short_interleaved(stream, info.channels, pcm, 32768);
	if (bytesRead) {
		if (info.channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else {
			format = AL_FORMAT_STEREO16;
		}
		alBufferData(buffer, format, pcm, bytesRead*info.channels*sizeof(uint16), info.sample_rate);
		samplesLeft -= bytesRead;
		return true;
	}else{
	return false;
	}
	}
