#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase

// forward declaration
class Collidable;

class CollisionDispatchBase
{
public:
	// big four
	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase&) = delete;
	CollisionDispatchBase& operator = (const CollisionDispatchBase&) = delete;
	virtual ~CollisionDispatchBase() = default;

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) = 0;
};

#endif