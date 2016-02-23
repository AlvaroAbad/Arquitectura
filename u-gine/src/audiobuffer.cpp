#include "..\include\audiobuffer.h"
#include "../include/file.h"
#include "../lib/openal/AL/al.h"
#include "../lib/openal/AL/alc.h"
#define STB_VORBIS_HEADER_ONLY
#include "../lib/stb_vorbis.c"
AudioBuffer::AudioBuffer(const String & filename)
{
	uint32 RiffChunkSize, FmtChunkSize, SampleRate, ByteRate, bufferSize, data;
	void * buffer;
	char texto[5];
	texto[4] = 0;
	uint16 AudioFormat, Channels, BlockAlign, BitsPerSample, ExtraParamsSize;
	alBuffer = 0;
	if (filename.ExtractExt() == "wav") {
		File * wavFile = new File(filename, 0);
		wavFile->ReadInt();//"RIFF"
		RiffChunkSize = wavFile->ReadInt();
		wavFile->ReadInt();//"WAVE"
		wavFile->ReadInt();//"fmt"
		FmtChunkSize = wavFile->ReadInt();
		AudioFormat = wavFile->ReadInt16();
		Channels = wavFile->ReadInt16();
		SampleRate = wavFile->ReadInt();
		ByteRate = wavFile->ReadInt();
		BlockAlign = wavFile->ReadInt16();
		BitsPerSample = wavFile->ReadInt16();
		if (FmtChunkSize > 16) {
			ExtraParamsSize = wavFile->ReadInt16();
			wavFile->Seek(wavFile->Pos() + ExtraParamsSize);
		}
		do {
			wavFile->ReadBytes(texto, 4);
		} while (String(texto) != "data");
		bufferSize = wavFile->ReadInt();
		buffer = malloc(bufferSize);
		wavFile->ReadBytes(buffer, bufferSize);
		ALenum format;
		if (BitsPerSample == 8) {
			if (Channels == 1) {
				format = AL_FORMAT_MONO8;
			}
			else {
				format = AL_FORMAT_STEREO8;
			}
		}
		else {
			if (Channels == 1) {
				format = AL_FORMAT_MONO16;
			}
			else {
				format = AL_FORMAT_STEREO16;
			}
		}

		alGenBuffers(1, &alBuffer);
		alBufferData(alBuffer, format, buffer, bufferSize, SampleRate);
		free(buffer);
	}
	else if (filename.ExtractExt() == "ogg") {
		stb_vorbis * structure;
		stb_vorbis_info info;
		uint32 length;
		int16 *buffer;
		structure = stb_vorbis_open_filename(filename.ToCString(), NULL, NULL);
		info = stb_vorbis_get_info(structure);
		length = stb_vorbis_stream_length_in_samples(structure)*info.channels;
		buffer = static_cast<int16*>(malloc(length*sizeof(uint16)));
		stb_vorbis_get_samples_short_interleaved(structure, info.channels, buffer, length);
		ALenum format;
		if (info.channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else {
			format = AL_FORMAT_STEREO16;
		}
		alGenBuffers(1, &alBuffer);
		alBufferData(alBuffer, format, buffer, length*sizeof(uint16), info.sample_rate);
		stb_vorbis_close(structure);
		free(buffer);
	}
}

AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, &alBuffer);
}
