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
	//Trace::out(" ---- collision manager shutting down ----\n");
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
	{
		colGroupCollection[idNum] = new CollidableGroup();
		//Trace::out("created new collidablegroup, #%i\n", idNum);
	}
	//else
		//Trace::out("using existing collidablegroup, #%i\n", idNum);
}

CollidableGroup* CollisionManager::GetColGroup(DockyardTypeID id)
{
	//Trace::out("GetColGroup returning group #%i\n", id);
	return colGroupCollection[id];
}

void CollisionManager::ProcessCollisions()
{
	for (CollisionTestCommands::iterator it = colTestCmds.begin(); it != colTestCmds.end(); it++)
	{
		(*it)->Execute();
	}
}