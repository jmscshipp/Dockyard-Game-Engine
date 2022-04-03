#ifndef _CollisionManager
#define _CollisionManager

#include <vector>
#include <list>
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionDispatch.h"

// forward declaration
class CollidableGroup;
class CollisionTestCommandBase;

class CollisionManager
{
public:
	// big four
	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator = (const CollisionManager&) = delete;
	~CollisionManager();

	using DockyardTypeID = int;
	static const DockyardTypeID TYPEID_UNDEFINED = -1;

private:
	static DockyardTypeID TypeIDNextNumber;
	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection colGroupCollection;

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands colTestCmds;

	void SetGroupForTypeID(DockyardTypeID idNum);

public:
	void ProcessCollisions();

	template <typename C>
	DockyardTypeID GetTypeID()
	{
		static DockyardTypeID myTypeID = TypeIDNextNumber++;

		SetGroupForTypeID(myTypeID);

		//Trace::out("Type ID: %i\n", myTypeID);
		return myTypeID;
	}

	CollidableGroup* GetColGroup(DockyardTypeID id);

	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* group1 = colGroupCollection[GetTypeID<C1>()];
		CollidableGroup* group2 = colGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();
		colTestCmds.push_back(new CollisionTestPairCommand(group1, group2, pDispatch));
	}

	template <typename C>
	void SetCollisionSelf()
	{
		CollidableGroup* group = colGroupCollection[GetTypeID<C>()];
		
		CollisionDispatch<C, C>* pDispatch = new CollisionDispatch<C, C>();
		colTestCmds.push_back(new CollisionTestSelfCommand(group, pDispatch));
	}
};

#endif