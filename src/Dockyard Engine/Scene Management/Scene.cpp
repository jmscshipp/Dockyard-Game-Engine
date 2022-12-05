#include "Scene.h"
#include "SceneRegistrationBroker.h"
#include "CameraManager.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "ALarmableManager.h"
#include "KeyboardEventManager.h"
#include "TerrainManager.h"
#include "NullTerrain.h"

Scene::Scene()
{
	registrationBrkr = new SceneRegistrationBroker();
	updatableMgr = new UpdatableManager();
	drawableMgr = new DrawableManager();
	alarmableMgr = new AlarmableManager();
	keyboardEventMgr = new KeyboardEventManager();
	collisionMgr = new CollisionManager();
	cameraMgr = new CameraManager();

	// set up null terrain as current
	nullTerrain = new NullTerrain();
	currentTerrain = nullTerrain;
}

Scene::~Scene()
{
	delete nullTerrain;
	delete registrationBrkr;
	delete updatableMgr;
	delete drawableMgr;
	delete alarmableMgr;
	delete keyboardEventMgr;
	delete collisionMgr;
	delete cameraMgr;
}

void Scene::Update()
{
	registrationBrkr->ExecuteCommands();
	collisionMgr->ProcessCollisions();
	keyboardEventMgr->ProcessKeyEvents();
	alarmableMgr->ProcessElements();
	updatableMgr->ProcessElements();
}

void Scene::Draw()
{
	currentTerrain->Render();
	drawableMgr->ProcessElements();
}

void Scene::SetCurrentCamera(Camera* cam)
{
	cameraMgr->SetCurrentCamera(cam);
}

void Scene::SetCurrentTerrain(std::string terrainName)
{
	currentTerrain = TerrainManager::GetTerrain(terrainName);
}

void Scene::SetCurrentTerrainToNull()
{
	currentTerrain = nullTerrain;
}

Terrain* Scene::GetCurrentTerrain()
{
	if (currentTerrain != nullTerrain)
		return static_cast<Terrain*>(currentTerrain);
}

Camera* Scene::GetCurrentCamera()
{
	return cameraMgr->GetCurrentCamera();
}

Camera* Scene::GetDefaultOrthoCam()
{
	return cameraMgr->GetDefaultOrthoCam();
}