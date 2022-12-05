#ifndef _GameObject
#define _GameObject

#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"

// forward declarations
class GameObjectEntryCommand;
class GameObjectExitCommand;

class GameObject : protected Updatable, protected Drawable, protected Alarmable, protected Inputable, protected Collidable
{
public:
	// big four
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator = (const GameObject&) = delete;
	~GameObject();

	void SubmitEntry();
	void SubmitExit();

private:
	void ConnectToScene();
	void DisconnectFromScene();

	virtual void SceneEntry() {};
	virtual void SceneExit() {};

	SceneRegistrationState currentState;
	GameObjectEntryCommand* myEntryCmd;
	GameObjectExitCommand* myExitCmd;

	friend class GameObjectAttorney;
};

#endif