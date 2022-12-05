#ifndef _Collidable
#define _Collidable

#include "SceneRegistrationState.h"
#include "SceneAttorney.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "Matrix.h"
#include "GraphicsCore.h"

// forward declarations
class CollisionVolume;

// forward declarations
class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;

class Collidable
{
public:
	// big four
	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator = (const Collidable&) = delete;
	virtual ~Collidable();

	const CollisionVolume& GetCollisionVolume();
	const CollisionVolumeBSphere& GetDefaultBSphere();
	virtual void CollisionTerrain() {};
	enum COLLISION_VOLUME_TYPE { BSPHERE, AABB, OBB};

private:
	CollisionManager::DockyardTypeID myID = CollisionManager::TYPEID_UNDEFINED;

	// scene registration
	void SceneRegistration();
	void SceneDeregistration();

	CollisionRegistrationCommand* registerCmd;
	CollisionDeregistrationCommand* deregisterCmd;
	SceneRegistrationState currentState;
	CollidableGroup::CollidableCollectionRef myDeletePtr;
	std::list<Vect*>::iterator minDefaultBSphereDeletePtr; // pointers to assign in collidable group min and max collections
	std::list<Vect*>::iterator maxDefaultBSphereDeletePtr;

	CollisionVolume* colVolume;
	Model* colliderModel;
	// for tiered collision test
	CollisionVolumeBSphere* defaultBSphere;

	friend class CollidableAttorney;

protected:
	template <typename C>
	void SetCollidableGroup()
	{
		myID = SceneAttorney::Registration::GetCollisionMgr()->GetTypeID<C>();
	}

	void SubmitCollisionRegistration();
	void SubmitCollisionDeregistration();

	// collision volume
	void SetColliderVolumeAndModel(COLLISION_VOLUME_TYPE volumeType, Model* mod);
	void UpdateCollisionData(const Matrix& mat);
};

#endif _Collidable