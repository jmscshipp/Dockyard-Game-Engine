#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>

// forward declaration
class Alarmable;

class AlarmableManager
{
public:
	// big four
	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator = (const AlarmableManager&) = delete;
	~AlarmableManager() = default;

	enum ALARM_ID { ALARM_0, ALARM_1, ALARM_2, ALARM_3, ALARM_4 };
	static const int ALARM_NUM = 5;

	using TimelineRef = std::multimap<float, std::pair<Alarmable*, ALARM_ID>>::iterator;

	void ProcessElements();
	void Register(float t, ALARM_ID id, Alarmable* alrm, TimelineRef &ref);
	void Deregister(TimelineRef ref);

private:
	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;
	using TimelineMap = std::multimap<float, AlarmEvent>;
	TimelineMap timeline;
};

#endif