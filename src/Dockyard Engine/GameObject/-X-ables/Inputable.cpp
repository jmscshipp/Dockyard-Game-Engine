#include "Inputable.h"
#include "SceneAttorney.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"

Inputable::Inputable()
{

}

Inputable::~Inputable()
{
	// get rid of press commmands
	for (RegDataMap::iterator it = pressRegData.begin(); it != pressRegData.end(); it++)
	{
		delete it->second.registerCmd;
		delete it->second.deregisterCmd;
	}
	// get rid of hold commmands
	for (RegDataMap::iterator it = holdRegData.begin(); it != holdRegData.end(); it++)
	{
		delete it->second.registerCmd;
		delete it->second.deregisterCmd;
	}
	// get rid of release commands
	for (RegDataMap::iterator it = releaseRegData.begin(); it != releaseRegData.end(); it++)
	{
		delete it->second.registerCmd;
		delete it->second.deregisterCmd;
	}
}


void Inputable::SubmitInputRegistration(KEY k, EVENT_TYPE e)
{
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		RegMapRef ref = pressRegData.find(k);
		if (ref == pressRegData.end()) // 
		{
			// setting up new registration data
			RegistrationData newData;
			newData.currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
			newData.registerCmd = new InputRegistrationCommand(this, k, e);
			newData.deregisterCmd = new InputDeregistrationCommand(this, k, e);
			// add data to our map
			ref = pressRegData.insert(pressRegData.end(), std::pair<KEY, RegistrationData>(k, newData));
			// give register data references to commands
			ref->second.registerCmd->AssignRegData(&ref->second);
			ref->second.deregisterCmd->AssignRegData(&ref->second);
		}
		// submit command and update status
		assert(ref->second.currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
		SceneAttorney::CommandSubmission::SubmitCommand(ref->second.registerCmd);
		ref->second.currentState = SceneRegistrationState::PENDING_REGISTRATION;
	}
	else if (e == EVENT_TYPE::KEY_HOLD)
	{
		RegMapRef ref = holdRegData.find(k);
		if (ref == holdRegData.end()) // 
		{
			// setting up new registration data
			RegistrationData newData;
			newData.currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
			newData.registerCmd = new InputRegistrationCommand(this, k, e);
			newData.deregisterCmd = new InputDeregistrationCommand(this, k, e);
			// add data to our map
			ref = holdRegData.insert(holdRegData.end(), std::pair<KEY, RegistrationData>(k, newData));
			// give register data references to commands
			ref->second.registerCmd->AssignRegData(&ref->second);
			ref->second.deregisterCmd->AssignRegData(&ref->second);
		}
		// submit command and update status
		assert(ref->second.currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
		SceneAttorney::CommandSubmission::SubmitCommand(ref->second.registerCmd);
		ref->second.currentState = SceneRegistrationState::PENDING_REGISTRATION;
	}
	else if (e == EVENT_TYPE::KEY_RELEASE)
	{
		RegMapRef ref = releaseRegData.find(k);
		if (ref == releaseRegData.end()) // 
		{
			// setting up new registration data
			RegistrationData newData;
			newData.currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
			newData.registerCmd = new InputRegistrationCommand(this, k, e);
			newData.deregisterCmd = new InputDeregistrationCommand(this, k, e);
			// add data to our map
			ref = releaseRegData.insert(releaseRegData.end(), std::pair<KEY, RegistrationData>(k, newData));
			// give register data references to commands
			ref->second.registerCmd->AssignRegData(&ref->second);
			//ref->second.deregisterCmd->AssignRegData(&ref->second);
		}
		// submit command and update status
		assert(ref->second.currentState == SceneRegistrationState::CURRENTLY_DEREGISTERED);
		SceneAttorney::CommandSubmission::SubmitCommand(ref->second.registerCmd);
		ref->second.currentState = SceneRegistrationState::PENDING_REGISTRATION;
	}
}

void Inputable::SubmitInputDeregistration(KEY k, EVENT_TYPE e)
{
	if (e == EVENT_TYPE::KEY_PRESS)
	{
		RegMapRef ref = pressRegData.find(k);
		if (ref == pressRegData.end())
		{
			// THROW ERROR
			throw("!!! ERROR: Trying to deregister input that hasn't been registered!\n");
		}
		else
		{
			assert(ref->second.currentState == SceneRegistrationState::CURRENTLY_REGISTERED);
			SceneAttorney::CommandSubmission::SubmitCommand(ref->second.deregisterCmd);
			ref->second.currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
		}
	}
	else if (e == EVENT_TYPE::KEY_RELEASE)
	{
		RegMapRef ref = releaseRegData.find(k);
		if (ref == releaseRegData.end())
		{
			// THROW ERROR
			throw("!!! ERROR: Trying to deregister input that hasn't been registered!\n");
		}
		else
		{
			assert(ref->second.currentState == SceneRegistrationState::CURRENTLY_REGISTERED);
			SceneAttorney::CommandSubmission::SubmitCommand(ref->second.deregisterCmd);
			ref->second.currentState = SceneRegistrationState::PENDING_DEREGISTRATION;
		}
	}
}

void Inputable::SceneRegistration(KEY k, EVENT_TYPE e, RegistrationData* r)
{
	assert(r->currentState == SceneRegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Registration::Register(this, k, e, r->myDeletePtr);
	r->currentState = SceneRegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(KEY k, EVENT_TYPE e, RegistrationData* r)
{
	assert(r->currentState == SceneRegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Registration::Deregister(k, e, r->myDeletePtr);
	r->currentState = SceneRegistrationState::CURRENTLY_DEREGISTERED;
}