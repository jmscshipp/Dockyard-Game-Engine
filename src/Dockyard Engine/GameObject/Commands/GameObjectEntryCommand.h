#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class GameObject;

class GameObjectEntryCommand : public SceneRegistrationCommand
{
public:
	// big four
	GameObjectEntryCommand() = delete;
	GameObjectEntryCommand(GameObject* thisGameObject);
	GameObjectEntryCommand(const GameObjectEntryCommand&) = delete;
	GameObjectEntryCommand& operator = (const GameObjectEntryCommand&) = delete;
	virtual ~GameObjectEntryCommand() = default;

	void Execute() override;

private:
	GameObject* myGameObject;
};

#endif