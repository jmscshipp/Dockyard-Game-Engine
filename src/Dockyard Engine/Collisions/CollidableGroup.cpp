#include "CollidableGroup.h"

void CollidableGroup::Register(Collidable* c, CollidableCollectionRef& ref)
{
	ref = collidableCol.insert(collidableCol.begin(), c);
	//Trace::out("collidable registered\n");
}

void CollidableGroup::Deregister(const CollidableCollectionRef& ref)
{
	collidableCol.erase(ref);
	//Trace::out("collidable deregistered\n");
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return collidableCol;
}