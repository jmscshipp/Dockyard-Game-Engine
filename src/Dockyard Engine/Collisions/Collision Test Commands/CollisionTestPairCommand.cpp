#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionDispatchBase.h"
#include "DockyardMathTools.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* dis)
	: pGroup1(g1),
	pGroup2(g2),
	dispatch(dis)
{
}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
	delete dispatch;
}

void CollisionTestPairCommand::Execute()
{
	const CollidableGroup::CollidableCollection& col1 = pGroup1->GetColliderCollection();
	const CollidableGroup::CollidableCollection& col2 = pGroup2->GetColliderCollection();

	for (auto it1 = col1.begin(); it1 != col1.end(); it1++)
	{
		const CollisionVolumeBSphere& bs1 = (*it1)->GetBSphere();
		for (auto it2 = col2.begin(); it2 != col2.end(); it2++)
		{
			const CollisionVolumeBSphere& bs2 = (*it2)->GetBSphere();

			if (MathFunctions::Intersect(bs1, bs2))
				dispatch->ProcessCallbacks(*it1, *it2);
		}
	}
}