#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "Collidable.h"
#include "CollisionVolumeBSphere.h"

#include "CollisionVisualizer.h"
#include "ColorLibrary.h"

CollidableGroup::CollidableGroup()
{
	groupCollider = new CollisionVolumeAABB();
}

CollidableGroup::~CollidableGroup()
{
	delete groupCollider;
}

void CollidableGroup::Register(Collidable* c, CollidableCollectionRef& ref)
{
	ref = collidableCol.insert(collidableCol.begin(), c);
}

void CollidableGroup::Deregister(const CollidableCollectionRef& ref)
{
	collidableCol.erase(ref);
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return collidableCol;
}

const CollisionVolumeAABB& CollidableGroup::GetGroupCollider()
{
	return *groupCollider;
}

void CollidableGroup::ComputeGroupColData()
{
	Vect min, max;
	min = max = (*collidableCol.begin())->GetDefaultBSphere().GetMin();
	for (Collidable* col : collidableCol)
	{
		Vect temp = col->GetDefaultBSphere().GetMin();
		if (temp.X() < min.X())
			min.X() = temp.X();
		if (temp.Y() < min.Y())
			min.Y() = temp.Y();
		if (temp.Z() < min.Z())
			min.Z() = temp.Z();

		temp = col->GetDefaultBSphere().GetMax();
		if (temp.X() > max.X())
			max.X() = temp.X();
		if (temp.Y() > max.Y())
			max.Y() = temp.Y();
		if (temp.Z() > max.Z())
			max.Z() = temp.Z();
	}
	groupCollider->ComputeData(min, max);
}