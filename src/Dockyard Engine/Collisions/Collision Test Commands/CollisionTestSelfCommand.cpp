#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionDispatchBase.h"
#include "DockyardMathTools.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* dis)
	: group(g),
	dispatch(dis)
{
}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
	delete dispatch;
}

void CollisionTestSelfCommand::Execute()
{
	const CollidableGroup::CollidableCollection& col = group->GetColliderCollection();

	for (auto it1 = col.begin(); it1 != col.end(); it1++)
	{
		const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();
		for (auto it2 = --col.end(); it2 != it1; it2--)
		{
			const CollisionVolumeBSphere& bs2 = (*it2)->GetBSphere();

			if (MathFunctions::Intersect(bs1, bs2))
				dispatch->ProcessCallbacks(*it1, *it2);
		}
	}
}