#include "CollisionDeregistrationCommand.h"
#include "CollidableAttorney.h"

CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* thisCollidable)
	:myCollidable(thisCollidable)
{
}

void CollisionDeregistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneDeregistration(myCollidable);
}