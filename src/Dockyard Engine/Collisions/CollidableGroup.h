#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

// forward declaration
class Collidable;

class CollidableGroup
{
public:
	// big four
	CollidableGroup() = default;
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator = (const CollidableGroup&) = delete;
	virtual ~CollidableGroup() = default;

	using CollidableCollection = std::list<Collidable*>;
	using CollidableCollectionRef = std::list<Collidable*>::iterator;
	
	void Register(Collidable* c, CollidableCollectionRef& ref);
	void Deregister(const CollidableCollectionRef& ref);
	const CollidableCollection& GetColliderCollection();

private:
	CollidableCollection collidableCol;
};

#endif