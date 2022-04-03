#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"

KeyboardEventManager::~KeyboardEventManager()
{
	// cleaning up single key managers
	for (MapKeyManager::iterator it = singleKeyMgrs.begin(); it != singleKeyMgrs.end(); it++)
		delete it->second;
}

void KeyboardEventManager::ProcessKeyEvents()
{
	for (MapKeyManager::iterator it = singleKeyMgrs.begin(); it != singleKeyMgrs.end(); it++)
		it->second->ProcessKeyEvent();
}

void KeyboardEventManager::Register(Inputable* inp, AZUL_KEY k, InputableAttorney::EVENT_TYPE e, InputableAttorney::InputColRef& ref)
{
	SingleKeyEventManager* keyEventMgr;

	// if this single key manager doesn't exist yet, create one and use it
	if (!singleKeyMgrs.count(k))
	{
		keyEventMgr = new SingleKeyEventManager(k);
		singleKeyMgrs.insert(std::pair<AZUL_KEY, SingleKeyEventManager*>(k, keyEventMgr));
	}
	else // otherwise use existing one
		keyEventMgr = singleKeyMgrs.find(k)->second;

	keyEventMgr->Register(inp, e, ref);
}

void KeyboardEventManager::Deregister(AZUL_KEY k, InputableAttorney::EVENT_TYPE e, InputableAttorney::InputColRef& ref)
{
	singleKeyMgrs.find(k)->second->Deregister(e, ref);
}