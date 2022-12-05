#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include "InputUtility.h"
#include <list>

// forward declaration
class Inputable;

class SingleKeyEventManager
{
private:
	KEY key;

	enum KEY_STATE { DOWN, UP };
	KEY_STATE currentState;

	using InputableCollection = std::list<Inputable*>;
	InputableCollection keyPressCol;
	InputableCollection keyHoldCol;
	InputableCollection keyReleaseCol;

public:
	enum EVENT_TYPE { KEY_PRESS, KEY_HOLD, KEY_RELEASE };
	using InputColRef = std::list<Inputable*>::iterator;

	// big four
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(KEY key);
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator = (const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() = default;

	void ProcessKeyEvent();
	void Register(Inputable * a, EVENT_TYPE e, InputColRef & ref);
	void Deregister(EVENT_TYPE e, InputColRef & ref);
};

#endif