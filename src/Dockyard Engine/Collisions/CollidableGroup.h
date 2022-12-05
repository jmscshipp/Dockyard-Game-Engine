#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

// forward declaration
class Collidable;
class CollisionVolumeAABB;

class CollidableGroup
{
public:
	// big four
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator = (const CollidableGroup&) = delete;
	virtual ~CollidableGroup();

	using CollidableCollection = std::list<Collidable*>;
	using CollidableCollectionRef = std::list<Collidable*>::iterator;
	
	void Register(Collidable* c, CollidableCollectionRef& ref);
	void Deregister(const CollidableCollectionRef& ref);
	const CollidableCollection& GetColliderCollection();
	const CollisionVolumeAABB& GetGroupCollider();

	void ComputeGroupColData();

private:
	CollidableCollection collidableCol;
	CollisionVolumeAABB* groupCollider;
};

#endif