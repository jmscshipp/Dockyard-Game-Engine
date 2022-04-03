#include "UpdateRegistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* thisUpdatable)
	:myUpdatable(thisUpdatable)
{
}

void UpdateRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneRegistration(myUpdatable);
}