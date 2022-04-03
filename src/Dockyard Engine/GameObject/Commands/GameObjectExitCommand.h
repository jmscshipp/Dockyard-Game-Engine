#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class GameObject;

class GameObjectExitCommand : public SceneRegistrationCommand
{
public:
	// big four
	GameObjectExitCommand() = delete;
	GameObjectExitCommand(GameObject* thisGameObject);
	GameObjectExitCommand(const GameObjectExitCommand&) = delete;
	GameObjectExitCommand& operator = (const GameObjectExitCommand&) = delete;
	virtual ~GameObjectExitCommand() = default;

	void Execute() override;

private:
	GameObject* myGameObject;
};

#endif