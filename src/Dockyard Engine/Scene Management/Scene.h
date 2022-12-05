#ifndef _Scene
#define _Scene

#include "CollisionManager.h"

// forward declarations
class SceneRegistrationBroker;
class SceneRegistrationCommand;
class CameraManager;
class UpdatableManager;
class DrawableManager;
class AlarmableManager;
class KeyboardEventManager;
class Camera;
class TerrainBase;
class Terrain;

class Scene
{
public:
	// big four
	Scene();
	Scene(const Scene&) = delete;
	Scene& operator = (const Scene&) = delete;
	virtual ~Scene();

	// functions for users to fill out in their scenes
	virtual void Initialize() = 0;
	virtual void SceneEnd() = 0;

	// camera manager functions
	void SetCurrentCamera(Camera* cam);
	Camera* GetCurrentCamera();
	Camera* GetDefaultOrthoCam();
	
	// terrain
	void SetCurrentTerrain(std::string terrainName);
	void SetCurrentTerrainToNull();
	Terrain* GetCurrentTerrain();

	friend class SceneAttorney;

private:
	// processes elements from <x>able managers
	void Update();
	void Draw();

	SceneRegistrationBroker* registrationBrkr;
	UpdatableManager* updatableMgr;
	DrawableManager* drawableMgr;
	AlarmableManager* alarmableMgr;
	KeyboardEventManager* keyboardEventMgr;
	CollisionManager* collisionMgr;
	CameraManager* cameraMgr;
	TerrainBase* currentTerrain;
	TerrainBase* nullTerrain;

protected:
	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		collisionMgr->SetCollisionPair<C1, C2>();
	}

	template<typename C>
	void SetCollisionSelf()
	{
		collisionMgr->SetCollisionSelf<C>();
	}

	template<typename C>
	void SetCollisionTerrain()
	{
		collisionMgr->SetCollisionTerrain<C>();
	}
};

#endif