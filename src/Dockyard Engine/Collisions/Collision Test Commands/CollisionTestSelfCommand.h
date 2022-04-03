#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "CollisionTestCommandBase.h"

// forward declaration
class CollidableGroup;
class CollisionDispatchBase;
class CollisionVolumeBSphere; // used in test

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:
	// big four
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* dis);
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand& operator = (const CollisionTestSelfCommand&) = delete;
	virtual ~CollisionTestSelfCommand();

	void Execute() override;

private:
	CollidableGroup* group;
	CollisionDispatchBase* dispatch;
};

#endif