/**
* Used To Decode/Encode *.wav File
*/

#pragma once

#include "../Core.h"



typedef struct
{
	Byte	ID[4];		// Must be "RIFF"
	UInt32	size;		// The value should be the file size(*.wav file) - 8
	Byte	format[4];	// Must be "WAVE"
}
WaveRIFFHeader;


typedef struct
{
	Byte	ID[4];	// Must be "fmt "
	UInt32	size;	// The value should be sizeof(WaveFormatBlock) - 8
	UInt16	formatTag;
	UInt16	channelCount;
	UInt32	samplesPerSecond;
	UInt32	averageBytesPerSecond;
	UInt16	blockAlign;
	UInt16	bitsPerSample;
}
WaveFormatBlock;


typedef struct
{
	Byte	ID[4];	// Must be "data"
	UInt32	size;	// Indicates the size in bytes of audio track
}
WaveDataBlock;


typedef enum
{
	WaveFormatTag_PCM			= 1,
	WaveFormatTag_IEEE_Float	= 3,
}
WaveFormatTag;


typedef struct
{
	Void*		buffer;
	SizeType	byteCount;

	WaveFormatTag	formatTag;
	SizeType		channelCount;
	SizeType		depth;				// Indicates how many bits used by a sample(a L/R audio frame)
	SizeType		samplesPerSecond;	// Indicates how many samples used in a second
}
Wave;


struct FWave
{
	Wave(*Construct)(SizeType byteCount, WaveFormatTag formatTag, SizeType channelCount, SizeType depth, SizeType samplesPerSecond);
	Void(*Destruct)(Wave* instance);


	Bool(*IsValid)(const Void* buffer, SizeType byteCount);

	Wave(*Decode)(const Void* buffer, SizeType byteCount);
	HeapMemory(*Encode)(const Wave* instance);
};

extern ENGINE_API struct FWave FWave;