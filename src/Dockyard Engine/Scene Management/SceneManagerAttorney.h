#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

// forward declaration
class Scene;

class SceneManagerAttorney
{
public:
	// big four
	SceneManagerAttorney() = default;
	SceneManagerAttorney(const SceneManagerAttorney&) = delete;
	SceneManagerAttorney& operator = (const SceneManagerAttorney&) = delete;
	~SceneManagerAttorney() = default;

	class General
	{
		friend class Dockyard;

		static void Update() { SceneManager::Update(); };
		static void Draw() { SceneManager::Draw(); };
		static void Delete() { SceneManager::Delete(); };
	};

	class Commands
	{
		friend class SceneChangeCommand;

		static void ChangeScene(Scene* sceneToChangeTo) { SceneManager::ChangeScene(sceneToChangeTo); };
	};

};

#endif