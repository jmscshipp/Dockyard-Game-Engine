#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* thisGameObject)
	:myGameObject(thisGameObject)
{
}

void GameObjectEntryCommand::Execute()
{
	GameObjectAttorney::Registration::ConnectToScene(myGameObject);
}