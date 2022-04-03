#ifndef _TimeManager
#define _TimeManager

#include "FreezeTime.h"

class TimeManager
{
private:
	static TimeManager* instance; // set up as singleton

	// big four
	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator = (const TimeManager&) = delete;
	~TimeManager();

	static TimeManager& Instance()
	{
		if (!instance)
			instance = new TimeManager();
		return *instance;
	};

	float PrivGetTime();
	float PrivGetFrameTime();

	void NonstaticProcessTime(); // float system time parameter if switch back to no freeze mode
	static void ProcessTime() { Instance().NonstaticProcessTime(); }

	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	friend class TimeManagerAttorney;

	FreezeTime frzTime;
	float currentTime;
	float frameTime;
	float previousTime;

public:
	static float GetTime() { return Instance().PrivGetTime(); }
	static float GetFrameTime() { return Instance().PrivGetFrameTime(); }
};

#endif