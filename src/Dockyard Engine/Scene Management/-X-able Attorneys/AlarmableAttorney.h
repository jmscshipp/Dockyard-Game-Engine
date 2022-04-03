#ifndef _AlarmableAttorney
#define _AlarmableAttorney

// forward declaration
#include "Alarmable.h"

class AlarmableAttorney
{
private:
	// big four
	AlarmableAttorney() = default;
	AlarmableAttorney(const AlarmableAttorney&) = delete;
	AlarmableAttorney& operator = (const AlarmableAttorney&) = delete;
	~AlarmableAttorney() = default;

public:
	class GameLoop
	{
		friend class AlarmableManager;
	private:
		static void TriggerAlarm(Alarmable* up, Alarmable::ALARM_ID id) { up->TriggerAlarm(id); }
	};

	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;
	public:
		using ALARM_ID = Alarmable::ALARM_ID;
	private:
		static void SceneRegistration(float t, Alarmable::ALARM_ID id, Alarmable* alrm) { alrm->SceneRegistration(id, t); }
		static void SceneDeregistration(Alarmable::ALARM_ID id, Alarmable* alrm) { alrm->SceneDeregistration(id); }
	};
};

#endif