#ifndef _InputableAttorney
#define _InputableAttorney

// forward declaration
#include "Inputable.h"

class InputableAttorney
{
public:
	// big four
	InputableAttorney() = default;
	InputableAttorney(const InputableAttorney&) = delete;
	InputableAttorney& operator = (const InputableAttorney&) = delete;
	~InputableAttorney() = default;

	using EVENT_TYPE = Inputable::EVENT_TYPE;
	using InputColRef = Inputable::InputColRef;
	using RegistrationData = Inputable::RegistrationData;

	class GameLoop
	{
		friend class SingleKeyEventManager;
	private:
		static void KeyPressed(Inputable* inp, AZUL_KEY k) { inp->KeyPressed(k); };
		static void KeyReleased(Inputable* inp, AZUL_KEY k) { inp->KeyReleased(k); };
	};

	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand;
	private:
		static void SceneRegistration(Inputable* inp, AZUL_KEY k, EVENT_TYPE e, RegistrationData* ref) { inp->SceneRegistration(k, e, ref); }
		static void SceneDeregistration(Inputable* inp, AZUL_KEY k, EVENT_TYPE e, RegistrationData* ref) { inp->SceneDeregistration(k, e, ref); }
	};
};

#endif