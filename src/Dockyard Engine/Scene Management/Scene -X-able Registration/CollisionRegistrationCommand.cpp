#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* thisCollidable)
	:myCollidable(thisCollidable)
{
}

void CollisionRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneRegistration(myCollidable);
}