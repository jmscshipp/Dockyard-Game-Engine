#include "CollisionTestPairCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionDispatchBase.h"
#include "DockyardMathTools.h"
#include "ColorLibrary.h"

#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

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
	// group AABB vs. group AABB
	if (MathFunctions::Intersect(pGroup1->GetGroupCollider(), pGroup2->GetGroupCollider()))
	{
		pGroup1->GetGroupCollider().DebugView(Colors::Blue);
		pGroup2->GetGroupCollider().DebugView(Colors::Red);

		const CollidableGroup::CollidableCollection& col1 = pGroup1->GetColliderCollection();

		// collidable default bsphere vs. other group AABB
		for (auto it1 = col1.begin(); it1 != col1.end(); it1++)
		{
			if (MathFunctions::Intersect((*it1)->GetDefaultBSphere(), pGroup2->GetGroupCollider()))
			{
				(*it1)->GetDefaultBSphere().DebugView(Colors::Red);

				const CollidableGroup::CollidableCollection& col2 = pGroup2->GetColliderCollection();

				// collidable default bsphere vs. collidable default bsphere in other group
				for (auto it2 = col2.begin(); it2 != col2.end(); it2++)
				{
					if (MathFunctions::Intersect((*it1)->GetDefaultBSphere(), (*it2)->GetDefaultBSphere()))
					{
						(*it1)->GetDefaultBSphere().DebugView(Colors::DarkRed);
						(*it2)->GetDefaultBSphere().DebugView(Colors::DarkRed);

						const CollisionVolume& v1 = (*it1)->GetCollisionVolume();
						const CollisionVolume& v2 = (*it2)->GetCollisionVolume();

						// user selected collision volume vs. user selected collision volume
						if (MathFunctions::Intersect(v1, v2))
						{
							v1.DebugView(Colors::LightGoldenrodYellow);
							v2.DebugView(Colors::LightGoldenrodYellow);

							dispatch->ProcessCallbacks(*it1, *it2);
						}
					}	
				}
			}
		}
	}
}