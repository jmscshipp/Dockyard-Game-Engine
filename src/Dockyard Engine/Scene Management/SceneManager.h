#ifndef _SceneManager
#define _SceneManager

#include "SceneRegistrationState.h"

// forward declaration
class Scene;
class SceneChangeCommandBase;

class SceneManager
{
private:
	static SceneManager* instance; // set up as singleton

	// big four
	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator = (const SceneManager&) = delete;
	~SceneManager();

	static SceneManager& Instance()
	{
		if (!instance)
			instance = new SceneManager();
		return *instance;
	};

	// Update, Draw, and Delete called by Dockyard
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); };
	void NonstaticDraw();
	static void Draw() { Instance().NonstaticDraw(); };
	void NonstaticUpdate();
	static void Update() { Instance().NonstaticUpdate(); };

	// called by by scene change command
	void NonstaticChangeScene(Scene* sceneToChangeTo);
	static void ChangeScene(Scene* sceneToChangeTo) { Instance().NonstaticChangeScene(sceneToChangeTo); };

	// private methods with public static versions
	Scene* PrivGetCurrentScene();
	void PrivSetNextScene(Scene* sceneToChangeTo);

	friend class SceneManagerAttorney;

	Scene* currentScene;
	SceneRegistrationState sceneChangeState;
	SceneChangeCommandBase* currentSceneChangeCmd; // points to one of the other two
	SceneChangeCommandBase* sceneChangeCmd;
	SceneChangeCommandBase* nullSceneChangeCmd;

public:
	static Scene* GetCurrentScene() { return Instance().PrivGetCurrentScene(); }
	static void SetNextScene(Scene* scene) { Instance().PrivSetNextScene(scene); }
};

#endif