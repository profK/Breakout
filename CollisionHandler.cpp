#include "CollisionHandler.h"
#include "PhysicsObject.h"

CollisionHandler::CollisionHandler(b2World& world)
{
	world.SetContactListener(this);
}

void CollisionHandler::BeginContact(b2Contact* contact)
{
	PhysicsObject* physObjPtr1 = (PhysicsObject*)contact->GetFixtureA()->GetUserData();
	PhysicsObject* physObjPtr2 = (PhysicsObject*)contact->GetFixtureB()->GetUserData();

	physObjPtr1->CollidedWith(*physObjPtr2);
	physObjPtr2->CollidedWith(*physObjPtr1);
}
