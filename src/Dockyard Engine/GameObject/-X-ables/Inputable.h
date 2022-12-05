#ifndef _Inputable
#define _Inputable

#include "SceneRegistrationState.h"
#include "SingleKeyEventManager.h"
#include "InputUtility.h"
#include <list> // for iterator ref
#include <map>

// forward declarations
class InputRegistrationCommand;
class InputDeregistrationCommand;
struct RegistrationData;

class Inputable
{
public:
	// big four
	Inputable();
	Inputable(const Inputable&) = delete;
	Inputable& operator = (const Inputable&) = delete;
	virtual ~Inputable();

	using EVENT_TYPE = SingleKeyEventManager::EVENT_TYPE;
	using InputColRef = SingleKeyEventManager::InputColRef;

private:

	struct RegistrationData
	{
		InputRegistrationCommand* registerCmd;
		InputDeregistrationCommand* deregisterCmd;
		SceneRegistrationState currentState;
		InputColRef myDeletePtr;
	};

	using RegDataMap = std::map<KEY, RegistrationData>;
	using RegMapRef = RegDataMap::iterator; // for use in submit registration
	RegDataMap pressRegData;
	RegDataMap holdRegData;
	RegDataMap releaseRegData;

	virtual void KeyPressed(KEY) {};
	virtual void KeyHeld(KEY) {};
	virtual void KeyReleased(KEY) {};
	void SceneRegistration(KEY k, EVENT_TYPE e, RegistrationData* r);
	void SceneDeregistration(KEY k, EVENT_TYPE e, RegistrationData* r);

	friend class InputableAttorney;

protected:
	void SubmitInputRegistration(KEY k, EVENT_TYPE e);
	void SubmitInputDeregistration(KEY k, EVENT_TYPE e);
};

#endif