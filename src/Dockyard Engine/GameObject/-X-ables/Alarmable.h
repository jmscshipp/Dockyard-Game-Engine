#ifndef _Alarmable
#define _Alarmable

#include "SceneRegistrationState.h"
#include "AlarmableManager.h"

// forward declarations
class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
public:
	// big four
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator = (const Alarmable&) = delete;
	virtual ~Alarmable();

	// public so commands can use them
	using ALARM_ID = AlarmableManager::ALARM_ID;

protected:
	void SubmitAlarmRegistration(ALARM_ID id, float t);
	void SubmitAlarmDeregistration(ALARM_ID id);

private:
	virtual void Alarm0() {};
	virtual void Alarm1() {};
	virtual void Alarm2() {};
	virtual void Alarm3() {};
	virtual void Alarm4() {};
	void TriggerAlarm(ALARM_ID id);
	void SceneRegistration(ALARM_ID id, float t);
	void SceneDeregistration(ALARM_ID id);

	struct RegistrationData
	{
		AlarmRegistrationCommand* registerCmd;
		AlarmDeregistrationCommand* deregisterCmd;
		SceneRegistrationState currentState;
		AlarmableManager::TimelineRef myDeletePtr;
	};

	RegistrationData regData[AlarmableManager::ALARM_NUM];
	RegistrationData* GetRegDataFromId(ALARM_ID id); // helper function

	friend class AlarmableAttorney;
};

#endif