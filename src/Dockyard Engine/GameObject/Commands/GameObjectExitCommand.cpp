#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* thisGameObject)
	:myGameObject(thisGameObject)
{
}

void GameObjectExitCommand::Execute()
{
	GameObjectAttorney::Registration::DisconnectFromScene(myGameObject);
}