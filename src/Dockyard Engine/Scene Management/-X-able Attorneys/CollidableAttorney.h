#ifndef _CollidableAttorney
#define _CollidableAttorney

// forward declaration
#include "Collidable.h"

class CollidableAttorney
{
public:
	// big four
	CollidableAttorney() = default;
	CollidableAttorney(const CollidableAttorney&) = delete;
	CollidableAttorney& operator = (const CollidableAttorney&) = delete;
	~CollidableAttorney() = default;

	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;
	private:
		static void SceneRegistration(Collidable* cldr) { cldr->SceneRegistration(); }
		static void SceneDeregistration(Collidable* cldr) { cldr->SceneDeregistration(); }
	};
};

#endif