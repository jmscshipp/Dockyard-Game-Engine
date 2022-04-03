#include "Alarmable.h"
#include "SceneAttorney.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"

Alarmable::Alarmable()
{
	// setting up each alarm
	for (int i = 0; i < AlarmableManager::ALARM_NUM; i++)
	{
		regData[i].currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
		regData[i].registerCmd = new AlarmRegistrationCommand(this, (ALARM_ID)i);
		regData[i].deregisterCmd = new AlarmDeregistrationCommand(this, (ALARM_ID)i);
	}
}

Alarmable::~Alarmable()
{
	// cleaning up alarm commands
	for (int i = 0; i < AlarmableManager::ALARM_NUM; i++)
	{
		delete regData[i].deregisterCmd;
		delete regData[i].registerCmd;
	}
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	switch (id)
	{
	case AlarmableManager::ALARM_0:
		regData[0].currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		regData[1].currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		regData[2].currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm2();
		break;
	case AlarmableManager::ALARM_3:
		regData[3].currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm3();
		break;
	case AlarmableManager::ALARM_4:
		regData[4].currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm4();
		break;
	default:
		// nothing
		break;
	}
}

void Alarmable::SubmitAlarmRegistration(ALARM_ID id, float t)
{
	RegistrationData* alarm = GetRegDataFromId(id);
	assert(alarm->currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
	alarm->registerCmd->SetTimeUntilTriggered(t);
	SceneAttorney::CommandSubmission::SubmitCommand(alarm->registerCmd);
	alarm->currentState = SceneRegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(ALARM_ID id)
{
	RegistrationData* alarm = GetRegDataFromId(id);
	assert(alarm->currentState == SceneRegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::CommandSubmission::SubmitCommand(alarm->deregisterCmd);
	alarm->currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::SceneRegistration(ALARM_ID id, float t)
{
	RegistrationData* alarm = GetRegDataFromId(id);
	assert(alarm->currentState == SceneRegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Registration::Register(t, id, this, alarm->myDeletePtr);
	alarm->currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::SceneDeregistration(ALARM_ID id)
{
	RegistrationData* alarm = GetRegDataFromId(id);
	assert(alarm->currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Registration::Deregister(alarm->myDeletePtr);
	alarm->currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}

Alarmable::RegistrationData* Alarmable::GetRegDataFromId(ALARM_ID id)
{
	switch (id)
	{
	case AlarmableManager::ALARM_0:
		return &regData[0];
		break;
	case AlarmableManager::ALARM_1:
		return &regData[1];
		break;
	case AlarmableManager::ALARM_2:
		return &regData[2];
		break;
	case AlarmableManager::ALARM_3:
		return &regData[3];
		break;
	case AlarmableManager::ALARM_4:
		return &regData[4];
		break;
	default:
		throw("!!! ERROR: nonexistant ALARM_ID used by Alarmable!\n");
		break;
	}
}