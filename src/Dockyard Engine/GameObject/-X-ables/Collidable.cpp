#include "Collidable.h"
#include "SceneAttorney.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"

Collidable::Collidable()
{
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
	registerCmd = new CollisionRegistrationCommand(this);
	deregisterCmd = new CollisionDeregistrationCommand(this);
}

Collidable::~Collidable()
{
	delete registerCmd;
	delete deregisterCmd;
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
	SceneAttorney::Registration::Register(this, myID, myDeletePtr);

	currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	//Trace::out("collidable deregistering from scene\n");

	SceneAttorney::Registration::Deregister(myID, myDeletePtr);
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}

const CollisionVolumeBSphere& Collidable::GetBSphere()
{
	return bSphere;
}

void Collidable::SetColliderModel(Model* mod)
{
	colliderModel = mod;
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	bSphere.ComputeData(colliderModel, mat);
}