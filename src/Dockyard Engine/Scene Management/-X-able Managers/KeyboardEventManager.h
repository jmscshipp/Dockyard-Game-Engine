#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include "InputableAttorney.h"
#include <map>

// forward declaration
class Inputable;
class SingleKeyEventManager;

class KeyboardEventManager
{
public:
	// big four
	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager& operator = (const KeyboardEventManager&) = delete;
	~KeyboardEventManager();

	void ProcessKeyEvents();
	void Register(Inputable* inp, AZUL_KEY k, InputableAttorney::EVENT_TYPE e, InputableAttorney::InputColRef &ref);
	void Deregister(AZUL_KEY k, InputableAttorney::EVENT_TYPE e, InputableAttorney::InputColRef& ref);

private:
	using MapKeyManager = std::map<AZUL_KEY, SingleKeyEventManager*>;
	MapKeyManager singleKeyMgrs;
};

#endif