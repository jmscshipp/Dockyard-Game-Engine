#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableAttorney.h"

class AlarmRegistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(Alarmable* thisUpdatable, Alarmable::ALARM_ID thisId);
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand& operator = (const AlarmRegistrationCommand&) = delete;
	virtual ~AlarmRegistrationCommand() = default;

	void SetTimeUntilTriggered(float t);
	void Execute() override;
	
private:
	Alarmable* myAlarmable;
	Alarmable::ALARM_ID id;
	float timeUntilTriggered;
};

#endif