#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "TimeManager.h"

void AlarmableManager::ProcessElements()
{
	TimelineRef it = timeline.begin();
	while (it != timeline.end() && (*it).first <= TimeManager::GetTime())
	{
		AlarmableAttorney::GameLoop::TriggerAlarm((*it).second.first, (*it).second.second);
		timeline.erase(it);
		it = timeline.begin(); // when element is erased, iterator becomes invalid so we need to reset it
	}
}

void AlarmableManager::Register(float t, ALARM_ID id, Alarmable* alrm, TimelineRef &ref)
{
	ref = timeline.insert(std::pair<float, AlarmEvent>(TimeManager::GetTime() + t, AlarmEvent(alrm, id)));
}

void AlarmableManager::Deregister(TimelineRef ref)
{
	timeline.erase(ref);
}