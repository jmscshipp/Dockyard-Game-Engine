#include "AlarmRegistrationCommand.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* thisAlarmable, Alarmable::ALARM_ID thisId)
	:myAlarmable(thisAlarmable),
	id(thisId),
	timeUntilTriggered(0.0f)
{
}

void AlarmRegistrationCommand::SetTimeUntilTriggered(float t)
{
	timeUntilTriggered = t;
}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::SceneRegistration(timeUntilTriggered, id, myAlarmable);
}