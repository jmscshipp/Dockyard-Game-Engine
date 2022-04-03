#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include "AzulCore.h"
#include "InputableAttorney.h"
#include <list>

// forward declaration
class Inputable;

class SingleKeyEventManager
{
private:
	AZUL_KEY key;

	enum KEY_STATE { DOWN, UP };
	KEY_STATE currentState;

	using InputableCollection = std::list<Inputable*>;
	using InputColRef = std::list<Inputable*>::iterator;
	InputableCollection keyPressCol;
	InputableCollection keyReleaseCol;

public:
	// big four
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(AZUL_KEY key);
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator = (const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() = default;

	void ProcessKeyEvent();
	void Register(Inputable * a, InputableAttorney::EVENT_TYPE e, InputColRef & ref);
	void Deregister(InputableAttorney::EVENT_TYPE e, InputColRef & ref);
};

#endif