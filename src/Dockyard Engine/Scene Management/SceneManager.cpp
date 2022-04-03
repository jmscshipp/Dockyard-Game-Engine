#include "SceneManager.h"
#include "SceneAttorney.h"
#include "SceneChangeCommandBase.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"
#include "SceneNull.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
	sceneChangeCmd = new SceneChangeCommand();
	nullSceneChangeCmd = new SceneChangeNullCommand();
	currentScene = new SceneNull();
	currentSceneChangeCmd = nullSceneChangeCmd;
	sceneChangeState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}

SceneManager::~SceneManager()
{
	delete sceneChangeCmd;
	delete nullSceneChangeCmd;
}

void SceneManager::NonstaticDraw()
{
	SceneAttorney::General::Draw(currentScene);
}

void SceneManager::NonstaticUpdate()
{
	currentSceneChangeCmd->Execute();
	SceneAttorney::General::Update(currentScene);
}

void SceneManager::NonstaticDelete()
{
	currentScene->SceneEnd();
	delete currentScene;
	delete instance;
	instance = nullptr;
}

Scene* SceneManager::PrivGetCurrentScene()
{
	return currentScene;
}

void SceneManager::NonstaticChangeScene(Scene* sceneToChangeTo)
{
	assert(sceneChangeState == SceneRegistrationState::PENDING_REGISTRATION);
	currentScene->SceneEnd();
	delete currentScene;
	currentScene = sceneToChangeTo;
	currentSceneChangeCmd = nullSceneChangeCmd;
	currentScene->Initialize();
	sceneChangeState = SceneRegistrationState::CURRENTLY_DEREGISTERED;// yes this is purposeful. since scenes are changed once, don't need to use registration check, only reregistered
}

void SceneManager::PrivSetNextScene(Scene* scene)
{
	assert(sceneChangeState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
	sceneChangeCmd->SetSceneToChangeTo(scene);
	currentSceneChangeCmd = sceneChangeCmd;
	sceneChangeState = SceneRegistrationState::PENDING_REGISTRATION;
}