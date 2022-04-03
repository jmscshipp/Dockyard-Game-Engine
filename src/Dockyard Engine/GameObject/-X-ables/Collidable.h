#ifndef _Collidable
#define _Collidable

#include "SceneRegistrationState.h"
#include "SceneAttorney.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionVolumeBSphere.h"
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

	const CollisionVolumeBSphere& GetBSphere();

private:
	CollisionManager::DockyardTypeID myID = CollisionManager::TYPEID_UNDEFINED;

	// scene registration
	void SceneRegistration();
	void SceneDeregistration();

	CollisionRegistrationCommand* registerCmd;
	CollisionDeregistrationCommand* deregisterCmd;
	SceneRegistrationState currentState;
	CollidableGroup::CollidableCollectionRef myDeletePtr;

	CollisionVolumeBSphere bSphere;
	Model* colliderModel;

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
	void SetColliderModel(Model* mod);
	void UpdateCollisionData(const Matrix& mat);
};

#endif