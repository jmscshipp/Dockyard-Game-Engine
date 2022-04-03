#include "GameObject.h"
#include "SceneAttorney.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"

GameObject::GameObject()
{
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
	myEntryCmd = new GameObjectEntryCommand(this);
	myExitCmd = new GameObjectExitCommand(this);
}

GameObject::~GameObject()
{
	delete myEntryCmd;
	delete myExitCmd;
}

void GameObject::SubmitEntry()
{
	assert(currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::CommandSubmission::SubmitCommand(myEntryCmd);
	currentState = SceneRegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	if (currentState == SceneRegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorney::CommandSubmission::SubmitCommand(myExitCmd);
		currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
	}
}

void GameObject::ConnectToScene()
{
	assert(currentState == SceneRegistrationState::PENDING_REGISTRATION);
	this->SceneEntry();
	currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::DisconnectFromScene()
{
	assert(currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	this->SceneExit();
	currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}