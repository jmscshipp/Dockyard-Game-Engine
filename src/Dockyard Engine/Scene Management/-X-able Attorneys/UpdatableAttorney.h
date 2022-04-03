#ifndef _UpdatableAttorney
#define _UpdatableAttorney

// forward declaration
#include "Updatable.h"

class UpdatableAttorney
{
public:
	// big four
	UpdatableAttorney() = default;
	UpdatableAttorney(const UpdatableAttorney&) = delete;
	UpdatableAttorney& operator = (const UpdatableAttorney&) = delete;
	~UpdatableAttorney() = default;

	class GameLoop
	{
		friend class UpdatableManager;
	private:
		static void Update(Updatable* up) { up->Update(); }
	};

	class Registration
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeregistrationCommand;
	private:
		static void SceneRegistration(Updatable* up) { up->SceneRegistration(); }
		static void SceneDeregistration(Updatable* up) { up->SceneDeregistration(); }
	};
};

#endif