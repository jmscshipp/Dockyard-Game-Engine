#include "SceneRegistrationBroker.h"
#include "SceneRegistrationCommand.h"

void SceneRegistrationBroker::AddCommand(SceneRegistrationCommand* command)
{
	lstCommands.push_back(command);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (SceneRegistrationCommand* command : lstCommands)
		command->Execute();

	lstCommands.clear();
}