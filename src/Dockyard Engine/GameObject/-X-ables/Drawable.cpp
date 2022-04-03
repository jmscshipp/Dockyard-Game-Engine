#include "Drawable.h"
#include "SceneAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"

Drawable::Drawable()
{
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
	registerCmd = new DrawRegistrationCommand(this);
	deregisterCmd = new DrawDeregistrationCommand(this);
}

Drawable::~Drawable()
{
	delete registerCmd;
	delete deregisterCmd;
}

void Drawable::SubmitDrawRegistration()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::CommandSubmission::SubmitCommand(registerCmd);
	currentState = SceneRegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::CommandSubmission::SubmitCommand(deregisterCmd);
	currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
}

void Drawable::SceneRegistration()
{
	assert(currentState == SceneRegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Registration::Register(this, myDeletePtr);
	currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Registration::Deregister(myDeletePtr);
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}