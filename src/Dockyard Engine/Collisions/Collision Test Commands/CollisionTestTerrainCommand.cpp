#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "Collidable.h"
#include "CollisionDispatchBase.h"
#include "DockyardMathTools.h"
#include "ColorLibrary.h"
#include "Terrain.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* g)
	: pGroup(g)
{
}

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
}

void CollisionTestTerrainCommand::Execute()
{
	const Terrain* terrain = SceneManager::GetCurrentScene()->GetCurrentTerrain();
	const CollidableGroup::CollidableCollection& collection = pGroup->GetColliderCollection();

	for (auto it = collection.begin(); it != collection.end(); it++)
	{
		terrain->Intersect(*it);
	}
}