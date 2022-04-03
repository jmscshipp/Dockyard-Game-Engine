#include "Scene.h"
#include "SceneRegistrationBroker.h"
#include "CameraManager.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "ALarmableManager.h"
#include "InputableAttorney.h"
#include "KeyboardEventManager.h"

Scene::Scene()
{
	registrationBrkr = new SceneRegistrationBroker();
	updatableMgr = new UpdatableManager();
	drawableMgr = new DrawableManager();
	alarmableMgr = new AlarmableManager();
	keyboardEventMgr = new KeyboardEventManager();
	collisionMgr = new CollisionManager();
	cameraMgr = new CameraManager();
}

Scene::~Scene()
{
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
	drawableMgr->ProcessElements();
}

void Scene::SetCurrentCamera(Camera* cam)
{
	cameraMgr->SetCurrentCamera(cam);
}

Camera* Scene::GetCurrentCamera()
{
	return cameraMgr->GetCurrentCamera();
}

Camera* Scene::GetDefaultOrthoCam()
{
	return cameraMgr->GetDefaultOrthoCam();
}