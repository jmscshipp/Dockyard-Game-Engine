#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
public:
	// big four
	TimeManagerAttorney() = default;
	TimeManagerAttorney(const TimeManagerAttorney&) = delete;
	TimeManagerAttorney& operator = (const TimeManagerAttorney&) = delete;
	~TimeManagerAttorney() = default;
	
	class System
	{
		friend class Dockyard;
	private:
		static void Delete() { TimeManager::Delete(); }
		static void ProcessTime() { TimeManager::ProcessTime(); } // need to propogate systemTime parameter through if switch from freeze mode
	};
};

#endif