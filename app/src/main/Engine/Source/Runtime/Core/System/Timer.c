#include "Timer.h"

#if defined(PLATFORM_WINDOWS)
#include "../../Platform/Windows/Windows.h"
#elif defined(PLATFORM_LINUX) | defined(PLATFORM_ANDROID)
#include <unistd.h>
#endif



static RealType CurrentSystemTime()
{
#if defined(PLATFORM_WINDOWS)
	static Float64 period = -1;
	if ( period < 0 )
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		period = 1.0 / frequency.QuadPart;
	}

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	return CAST( RealType, period * counter.QuadPart );
#else
	struct timespec current;
	clock_gettime(CLOCK_MONOTONIC, &current);

	return current.tv_sec + current.tv_nsec / 1E9;
#endif
}


static Timer Construct()
{
	Timer ret;
	FTimer.Reset(&ret);

	return ret;
}

static Void Reset(Timer* instance)
{
	instance->start = CurrentSystemTime();
}

static RealType Elapsed(const Timer* instance)
{
	return CurrentSystemTime() - instance->start;
}


struct FTimer FTimer =
{
	Construct,
	Reset,
	Elapsed,
};
