#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "AlarmableAttorney.h"

// forward declaration
class Alarmable;

class AlarmDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	AlarmDeregistrationCommand() = delete;
	AlarmDeregistrationCommand(Alarmable* thisAlarmable, Alarmable::ALARM_ID thisId);
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = delete;
	AlarmDeregistrationCommand& operator = (const AlarmDeregistrationCommand&) = delete;
	virtual ~AlarmDeregistrationCommand() = default;

	void Execute() override;

private:
	Alarmable* myAlarmable;
	Alarmable::ALARM_ID id;
};

#endif