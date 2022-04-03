#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand

#include "SceneRegistrationCommand.h"

// forward declaration
class Collidable;

class CollisionDeregistrationCommand : public SceneRegistrationCommand
{
public:
	// big four
	CollisionDeregistrationCommand() = delete;
	CollisionDeregistrationCommand(Collidable* thisCollidable);
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand&) = delete;
	CollisionDeregistrationCommand& operator = (const CollisionDeregistrationCommand&) = delete;
	virtual ~CollisionDeregistrationCommand() = default;

	void Execute() override;

private:
	Collidable* myCollidable;
};

#endif