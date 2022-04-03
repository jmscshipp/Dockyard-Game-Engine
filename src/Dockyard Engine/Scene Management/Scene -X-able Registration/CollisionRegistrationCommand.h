#ifndef _CollisionRegistrationCommand
#define _CollisionRegistrationCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class Collidable;

class CollisionRegistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	CollisionRegistrationCommand() = delete;
	CollisionRegistrationCommand(Collidable* thisCollidable);
	CollisionRegistrationCommand(const CollisionRegistrationCommand&) = delete;
	CollisionRegistrationCommand& operator = (const CollisionRegistrationCommand&) = delete;
	virtual ~CollisionRegistrationCommand() = default;

	void Execute() override;

private:
	Collidable* myCollidable;
};

#endif