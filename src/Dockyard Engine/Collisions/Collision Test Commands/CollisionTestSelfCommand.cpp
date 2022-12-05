#include "CollisionTestSelfCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionDispatchBase.h"
#include "DockyardMathTools.h"

#include "CollisionVisualizer.h"
#include "ColorLibrary.h"

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
		for (auto it2 = --col.end(); it2 != it1; it2--)
		{
			// collidable default bsphere vs. collidable default bsphere
			if (MathFunctions::Intersect((*it1)->GetDefaultBSphere(), (*it2)->GetDefaultBSphere()))
			{
				//(*it1)->GetDefaultBSphere().DebugView(Colors::Purple);
				//(*it2)->GetDefaultBSphere().DebugView(Colors::Purple);

				const CollisionVolume& v1 = (*it1)->GetCollisionVolume();
				const CollisionVolume& v2 = (*it2)->GetCollisionVolume();

				// user selected collision volume vs. user selected collision volume
				if (MathFunctions::Intersect(v1, v2))
				{
					//v1.DebugView(Colors::MediumBlue);
					//v2.DebugView(Colors::MediumBlue);

					dispatch->ProcessCallbacks(*it1, *it2);
				}
			}
		}
	}
}