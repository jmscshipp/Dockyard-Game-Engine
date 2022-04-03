#include "Updatable.h"
#include "SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

Updatable::Updatable()
{
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
	registerCmd = new UpdateRegistrationCommand(this);
	deregisterCmd = new UpdateDeregistrationCommand(this);
}

Updatable::~Updatable()
{
	delete registerCmd;
	delete deregisterCmd;
}

void Updatable::SubmitUpdateRegistration()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::CommandSubmission::SubmitCommand(registerCmd);
	currentState = SceneRegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitUpdateDeregistration()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::CommandSubmission::SubmitCommand(deregisterCmd);
	currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
}

void Updatable::SceneRegistration()
{
	assert(currentState == SceneRegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Registration::Register(this, myDeletePtr);
	currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	assert(currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Registration::Deregister(myDeletePtr);
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}