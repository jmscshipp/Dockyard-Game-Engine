#ifndef _CollisionDispatch
#define _CollisionDispatch

#include "CollisionDispatchBase.h"

template <typename C1, typename C2>
class CollisionDispatch : public CollisionDispatchBase
{
public:
	// big four
	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch&) = delete;
	CollisionDispatch& operator = (const CollisionDispatch&) = delete;
	virtual ~CollisionDispatch() = default;

	void ProcessCallbacks(Collidable* c1, Collidable* c2) override
	{
		// convert collidables into derived user classes
		C1* derivedCol1 = static_cast<C1*>(c1);
		C2* derivedCol2 = static_cast<C2*>(c2);

		// call each callback
		derivedCol1->Collision(derivedCol2);
		derivedCol2->Collision(derivedCol1);
	}
};

#endif