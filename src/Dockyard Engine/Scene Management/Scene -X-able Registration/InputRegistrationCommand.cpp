#include "InputRegistrationCommand.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* thisInputable, AZUL_KEY k, InputableAttorney::EVENT_TYPE e)
	: myInputable(thisInputable),
	key(k),
	evnt(e),
	regData(nullptr)
{
}

void InputRegistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneRegistration(myInputable, key, evnt, regData);
}

void InputRegistrationCommand::AssignRegData(InputableAttorney::RegistrationData* ref)
{
	regData = ref;
}