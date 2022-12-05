#include "SingleKeyEventManager.h"
#include "Dockyard.h"
#include "InputableAttorney.h"

SingleKeyEventManager::SingleKeyEventManager(KEY k)
	: key(k),
	currentState(KEY_STATE::UP)
{
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	const bool keyState = InputUtility::GetKeyInputState(key);

	// key press
	if (keyState && currentState == KEY_STATE::UP)
	{
		for (InputableCollection::iterator it = keyPressCol.begin(); it != keyPressCol.end(); it++)
			InputableAttorney::GameLoop::KeyPressed(*it, key);
		currentState = KEY_STATE::DOWN;
	}
	// key hold
	else if (keyState && currentState == KEY_STATE::DOWN)
	{
		for (InputableCollection::iterator it = keyHoldCol.begin(); it != keyHoldCol.end(); it++)
			InputableAttorney::GameLoop::KeyHeld(*it, key);
	}
	// key release
	else if (!keyState && currentState == KEY_STATE::DOWN)
	{
		for (InputableCollection::iterator it = keyPressCol.begin(); it != keyPressCol.end(); it++)
			InputableAttorney::GameLoop::KeyReleased(*it, key);
		currentState = KEY_STATE::UP;
	}
}

void SingleKeyEventManager::Register(Inputable* a, InputableAttorney::EVENT_TYPE e, InputColRef& ref)
{
	if (e == InputableAttorney::EVENT_TYPE::KEY_PRESS)	// key press
		ref = keyPressCol.insert(keyPressCol.end(), a);
	else if (e == InputableAttorney::EVENT_TYPE::KEY_HOLD)	// key hold
		ref = keyHoldCol.insert(keyHoldCol.end(), a);
	else if (e == InputableAttorney::EVENT_TYPE::KEY_RELEASE)	// key release
		ref = keyReleaseCol.insert(keyReleaseCol.end(), a);
}

void SingleKeyEventManager::Deregister(InputableAttorney::EVENT_TYPE e, InputColRef& ref)
{
	if (e == InputableAttorney::EVENT_TYPE::KEY_PRESS)	// key press
		keyPressCol.erase(ref);
	else if (e == InputableAttorney::EVENT_TYPE::KEY_HOLD)	// key hold
		keyHoldCol.erase(ref);
	else if (e == InputableAttorney::EVENT_TYPE::KEY_RELEASE)	// key release
		keyReleaseCol.erase(ref);
}