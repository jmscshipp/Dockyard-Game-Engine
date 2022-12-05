#include "Collidable.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

#include "CollisionVisualizer.h"
#include "ColorLibrary.h"

Collidable::Collidable()
	: registerCmd(new CollisionRegistrationCommand(this)),
	deregisterCmd(new CollisionDeregistrationCommand(this)),
	currentState(SceneRegistrationState::CURRENTLY_DEREGISTERED),
	colVolume(nullptr),
	colliderModel(nullptr),
	defaultBSphere(nullptr)
{
}

Collidable::~Collidable()
{
	delete registerCmd;
	delete deregisterCmd;
	delete colVolume;
	delete defaultBSphere;
}

void Collidable::SubmitCollisionRegistration()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
	//Trace::out("collidable submitted collision registration\n");
	SceneAttorney::CommandSubmission::SubmitCommand(registerCmd);
	currentState = SceneRegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_REGISTERED);
	//Trace::out("collidable submitted collision deregistration\n");

	SceneAttorney::CommandSubmission::SubmitCommand(deregisterCmd);
	currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::SceneRegistration()
{
	assert(currentState == SceneRegistrationState::PENDING_REGISTRATION);
	//Trace::out("collidable registering to scene\n");
	SceneAttorney::Registration::Register(this, myID, myDeletePtr); // PLUG IN DELETE PTRS HEREEE

	currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	//Trace::out("collidable deregistering from scene\n");

	SceneAttorney::Registration::Deregister(myID, myDeletePtr);
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}

const CollisionVolume& Collidable::GetCollisionVolume()
{
	return *colVolume;
}

const CollisionVolumeBSphere& Collidable::GetDefaultBSphere()
{
	return *defaultBSphere;
}

void Collidable::SetColliderVolumeAndModel(COLLISION_VOLUME_TYPE volumeType, Model* mod)
{
	colliderModel = mod;
	if (volumeType == COLLISION_VOLUME_TYPE::BSPHERE)
		colVolume = new CollisionVolumeBSphere();
	else if (volumeType == COLLISION_VOLUME_TYPE::AABB)
		colVolume = new CollisionVolumeAABB();
	else
		colVolume = new CollisionVolumeOBB();

	defaultBSphere = new CollisionVolumeBSphere();
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	defaultBSphere->ComputeData(colliderModel, mat);
	colVolume->ComputeData(colliderModel, mat);
}