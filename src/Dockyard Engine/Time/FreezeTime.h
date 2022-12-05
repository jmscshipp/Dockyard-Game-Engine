#ifndef _FreezeTime
#define _FreezeTime

#include "InputUtility.h"
#include <chrono>

class FreezeTime
{
private:
	static const KEY FREEZE_KEY = KEY::F10_KEY;
	static const KEY SINGLE_FRAME_KEY = KEY::F9_KEY;

	static const float DEAD_TIME_THRESHOLD;
	static const float DEFAULT_FRAME_TIME;

	float totalFrozenTime;
	bool freeze_mode_active;

	using clock = std::chrono::high_resolution_clock;
	clock::time_point startTime;

	bool HackedKeyRelease(KEY k);
	void TestForFreezeKeys();

public:
	FreezeTime();
	~FreezeTime() {};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	float ComputeGameTime(float prev_time);
};

#endif _FreezeTime