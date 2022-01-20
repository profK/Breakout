#include "CollisionHandler.h"
#include "PhysicsObject.h"



/// <summary>
/// The constructor
/// </summary>
/// <param name="world">A reference to the Box2D world to install this handler into</param>
CollisionHandler::CollisionHandler(b2World& world)
{
	world.SetContactListener(this);
}

/// <summary>
/// This is the collision function.  It fires once for any collision, in the first
/// frame in which the object bodies overlap
/// </summary>
/// <param name="contact">Information from Box2D about the collision</param>
/// 
void CollisionHandler::BeginContact(b2Contact* contact)
{
	// The user data is a pointer to the PhysicsObject part of a game object
	// See the cosntructor of PhysicsObject for how it gets set
	PhysicsObject* physObjPtr1 = (PhysicsObject*)contact->GetFixtureA()->GetUserData(); 
	PhysicsObject* physObjPtr2 = (PhysicsObject*)contact->GetFixtureB()->GetUserData();

	//Call the CollidedWith method on each object woth the other as its parameter
	physObjPtr1->CollidedWith(*physObjPtr2);
	physObjPtr2->CollidedWith(*physObjPtr1);
}
