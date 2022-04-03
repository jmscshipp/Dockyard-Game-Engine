#ifndef _Updatable
#define _Updatable

#include "SceneRegistrationState.h"
#include "UpdatableManager.h"

// forward declarations
class UpdateRegistrationCommand;
class UpdateDeregistrationCommand;

class Updatable
{
public:
	// big four
	Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator = (const Updatable&) = delete;
	virtual ~Updatable();

protected:
	void SubmitUpdateRegistration();
	void SubmitUpdateDeregistration();

private:
	virtual void Update() {};
	void SceneRegistration();
	void SceneDeregistration();

	UpdateRegistrationCommand* registerCmd;
	UpdateDeregistrationCommand* deregisterCmd;
	SceneRegistrationState currentState;
	UpdatableManager::StorageListRef myDeletePtr; // set in updatablemanager register

	friend class UpdatableAttorney;	// this is so commands can access scene (de)registration()
};

#endif