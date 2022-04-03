#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "SceneRegistrationCommand.h"
#include "InputableAttorney.h"

class InputDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	InputDeregistrationCommand() = delete;
	InputDeregistrationCommand(Inputable* thisInputable, AZUL_KEY k, InputableAttorney::EVENT_TYPE e);
	InputDeregistrationCommand(const InputDeregistrationCommand&) = delete;
	InputDeregistrationCommand& operator = (const InputDeregistrationCommand&) = delete;
	virtual ~InputDeregistrationCommand() = default;

	void Execute() override;
	void AssignRegData(InputableAttorney::RegistrationData* ref);

private:
	Inputable* myInputable;
	AZUL_KEY key;
	InputableAttorney::EVENT_TYPE evnt;
	InputableAttorney::RegistrationData* regData;
};

#endif