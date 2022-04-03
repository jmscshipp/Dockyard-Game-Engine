#ifndef _Inputable
#define _Inputable

#include "SceneRegistrationState.h"
#include "AzulCore.h"
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

	enum EVENT_TYPE { KEY_PRESS, KEY_RELEASE };

private:
	
	using InputColRef = std::list<Inputable*>::iterator;

	struct RegistrationData
	{
		InputRegistrationCommand* registerCmd;
		InputDeregistrationCommand* deregisterCmd;
		SceneRegistrationState currentState;
		InputColRef myDeletePtr;
	};

	using RegDataMap = std::map<AZUL_KEY, RegistrationData>;
	using RegMapRef = RegDataMap::iterator; // for use in submit registration
	RegDataMap pressRegData;
	RegDataMap releaseRegData;

	virtual void KeyPressed(AZUL_KEY) {};
	virtual void KeyReleased(AZUL_KEY) {};
	void SceneRegistration(AZUL_KEY k, EVENT_TYPE e, RegistrationData* r);
	void SceneDeregistration(AZUL_KEY k, EVENT_TYPE e, RegistrationData* r);

	friend class InputableAttorney;

protected:
	void SubmitInputRegistration(AZUL_KEY k, EVENT_TYPE e);
	void SubmitInputDeregistration(AZUL_KEY k, EVENT_TYPE e);
};

#endif