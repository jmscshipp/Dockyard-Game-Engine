#include "InputDeregistrationCommand.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* thisInputable, KEY k, InputableAttorney::EVENT_TYPE e)
	: myInputable(thisInputable),
	key(k),
	evnt(e),
	regData(nullptr)
{
}

void InputDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneDeregistration(myInputable, key, evnt, regData);
}

void InputDeregistrationCommand::AssignRegData(InputableAttorney::RegistrationData* ref)
{
	regData = ref;
}