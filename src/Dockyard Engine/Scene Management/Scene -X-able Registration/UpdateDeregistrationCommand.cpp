#include "UpdateDeregistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* thisUpdatable)
	:myUpdatable(thisUpdatable)
{
}

void UpdateDeregistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneDeregistration(myUpdatable);
}