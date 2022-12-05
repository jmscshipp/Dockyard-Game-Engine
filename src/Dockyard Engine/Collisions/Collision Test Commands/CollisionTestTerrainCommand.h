#ifndef _CollisionTestTerrainCommand
#define _CollisionTestTerrainCommand

#include "CollisionTestCommandBase.h"

// forward declaration
class CollidableGroup;
class CollisionDispatchBase;

class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
public:
	// big four
	CollisionTestTerrainCommand() = delete;
	CollisionTestTerrainCommand(CollidableGroup* g);
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand& operator = (const CollisionTestTerrainCommand&) = delete;
	virtual ~CollisionTestTerrainCommand();

	void Execute() override;

private:
	CollidableGroup* pGroup;
};

#endif