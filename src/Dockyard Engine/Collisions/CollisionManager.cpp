#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionTestCommandBase.h"

CollisionManager::DockyardTypeID CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager()
{
	colGroupCollection = CollidableGroupCollection(200, nullptr); // hardcoded limit of 200
	colTestCmds = {};
}

CollisionManager::~CollisionManager()
{
	// delete collidable groups
	for (std::vector<CollidableGroup*>::iterator it = colGroupCollection.begin(); it != colGroupCollection.end(); it++)
	{
		if (*it != nullptr)
			delete* it;
	}
	// delete collision test commands
	for (CollisionTestCommands::iterator it = colTestCmds.begin(); it != colTestCmds.end(); it++)
	{
		delete (*it);
	}
}

void CollisionManager::SetGroupForTypeID(DockyardTypeID idNum)
{
	if (colGroupCollection[idNum] == nullptr)
		colGroupCollection[idNum] = new CollidableGroup();
}

CollidableGroup* CollisionManager::GetColGroup(DockyardTypeID id)
{
	return colGroupCollection[id];
}

void CollisionManager::ProcessCollisions()
{
	// update group aabbs
	for (CollidableGroup* colGroup : colGroupCollection)
	{
		if (colGroup != nullptr)
			colGroup->ComputeGroupColData();
	}
	// go through each pair or individual test
	for (CollisionTestCommands::iterator it = colTestCmds.begin(); it != colTestCmds.end(); it++)
		(*it)->Execute();
}