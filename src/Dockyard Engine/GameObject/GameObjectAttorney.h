#ifndef _GameObjectAttorney
#define _GameObjectAttorney

// forward declaration
#include "GameObject.h"

class GameObjectAttorney
{
public:
	// big four
	GameObjectAttorney() = default;
	GameObjectAttorney(const GameObjectAttorney&) = delete;
	GameObjectAttorney& operator = (const GameObjectAttorney&) = delete;
	~GameObjectAttorney() = default;

	class Registration
	{
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;
	private:
		static void ConnectToScene(GameObject* obj) { obj->ConnectToScene(); }
		static void DisconnectFromScene(GameObject* obj) { obj->DisconnectFromScene(); }
	};
};

#endif