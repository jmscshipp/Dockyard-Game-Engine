#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CollisionTestCommandBase.h"

// forward declaration
class CollidableGroup;
class CollisionDispatchBase;
class CollisionVolumeBSphere; // used in test

class CollisionTestPairCommand: public CollisionTestCommandBase
{
public:
	// big four
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* dis);
	CollisionTestPairCommand(const CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand& operator = (const CollisionTestPairCommand&) = delete;
	virtual ~CollisionTestPairCommand();

	void Execute() override;

private:
	CollidableGroup* pGroup1;
	CollidableGroup* pGroup2;
	CollisionDispatchBase* dispatch;
};

#endif