#include "AlarmDeregistrationCommand.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* thisAlarmable, Alarmable::ALARM_ID thisId)
	:myAlarmable(thisAlarmable),
	id(thisId)
{
}

void AlarmDeregistrationCommand::Execute()
{
	AlarmableAttorney::Registration::SceneDeregistration(id, myAlarmable);
}