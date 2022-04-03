#include "SingleKeyEventManager.h"
#include "Dockyard.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
	: key(k),
	currentState(KEY_STATE::UP)
{
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	// key press
	if (Keyboard::GetKeyState(key) && currentState == KEY_STATE::UP)
	{
		for (InputableCollection::iterator it = keyPressCol.begin(); it != keyPressCol.end(); it++)
			InputableAttorney::GameLoop::KeyPressed(*it, key);
		currentState = KEY_STATE::DOWN;
	}
	// key release
	else if (!Keyboard::GetKeyState(key) && currentState == KEY_STATE::DOWN)
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
	else if (e == InputableAttorney::EVENT_TYPE::KEY_RELEASE)	// key release
		ref = keyReleaseCol.insert(keyReleaseCol.end(), a);
}

void SingleKeyEventManager::Deregister(InputableAttorney::EVENT_TYPE e, InputColRef& ref)
{
	if (e == InputableAttorney::EVENT_TYPE::KEY_PRESS)	// key press
		keyPressCol.erase(ref);
	else if (e == InputableAttorney::EVENT_TYPE::KEY_RELEASE)	// key release
		keyReleaseCol.erase(ref);
}