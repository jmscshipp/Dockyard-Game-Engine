#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "SceneRegistrationCommand.h"
#include "InputableAttorney.h"
#include "InputUtility.h"

class InputRegistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	InputRegistrationCommand() = delete;
	InputRegistrationCommand(Inputable* thisInputable, KEY k, InputableAttorney::EVENT_TYPE e);
	InputRegistrationCommand(const InputRegistrationCommand&) = delete;
	InputRegistrationCommand& operator = (const InputRegistrationCommand&) = delete;
	virtual ~InputRegistrationCommand() = default;

	void Execute() override;
	void AssignRegData(InputableAttorney::RegistrationData* ref);

private:
	Inputable* myInputable;
	KEY key;
	InputableAttorney::EVENT_TYPE evnt;
	InputableAttorney::RegistrationData* regData;
};

#endif