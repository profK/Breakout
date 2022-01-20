#include "PhysicsObject.h"
#include <iostream>
using namespace sf;
using namespace std;

const float boxScaleFactor= 100;

#define DEBUG_COLLISION  true

/// <summary>
/// This is the constructor for a PhysicsObject.  It si compolex because it has to set up all the
/// Box2D paremeters for the object.  
/// </summary>
/// <param name="world">A reference to the Box2D simulation world this object belongs to</param>
/// <param name="otype">The type of the object as per the above enum</param>
/// <param name="centerPosition">The center of the rectangular bounding box the body represents</param>
/// <param name="size">The wdith and height of the bounding box</param>
PhysicsObject::PhysicsObject(b2World& world, ObjectType otype, Vector2f centerPosition, Vector2f size):
	world(world)
{
	// scale the pixel width and size to Box2D coords
	centerPosition /= boxScaleFactor; 
	size /= boxScaleFactor;
	objType = otype; // set the object type to be read in collisions
	// setup phsics
	// Moving objects need to have dynamic bodies, non-moving ones
	// should have static bodies for efficiency
	b2BodyDef bodyDef;
	if ((otype == BallType)||(otype == PaddleType)) {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_staticBody;
	}
	//set the location of the center of the bounding rectangle
	bodyDef.position.Set(centerPosition.x, centerPosition.y);
	bodyDef.linearDamping = 0.0f; // set drag to 0
	// this takes all the info w set in bodyDef and creates a physics body
	body = world.CreateBody(&bodyDef);
	// thsi sets the actual boundign rectangle.  Box2D supports other
	// boundign shapes but rectangles are most efficient and all we need for
	// this simple game
	// strat by making a box2D shape
	b2PolygonShape box;
	box.SetAsBox(size.x/2,size.y/2);
	// Fixtures are used to set properties on the body
	// we will use one here to set the collision rectangle and its properties
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box; // use the box we defined as the collision geometry
	fixtureDef.density = 1.0f; // it has a density of 1, this is used in momentum calculations
	fixtureDef.restitution = 1.0f; // it has a restitution of one, this means that a bounce preserves all speed
	fixtureDef.friction = 0; // this means rubbing against another body doesnt reduce the speed
	fixtureDef.userData = this;  // we store a pointer to this physics object to use in collision logic
	body->CreateFixture(&fixtureDef); //just as we created a body in the world, this takes our fixture 
	                                  // definition and creates a fixture on this particualr body
}


/// <summary>
/// A getter for the object type
/// </summary>
/// <returns>The object type set at construction</returns>
ObjectType PhysicsObject::GetObjType()
{
	return objType;
}

/// <summary>
/// A useful debug that prints the textual name of this
/// physics object's object type.  E.g.  "BallType"
/// </summary>
void PhysicsObject::PrintObjectTypeName()
{
	switch (objType) {
	case BallType:
		cout <<string("Ball");
		break;
	case WallType:
		cout<< string("Wall");
		break;
	case BrickType:
		cout<< string("Brick");
		break;
	default:
		cout<< string("Unknown Type");
	}
}

/// <summary>
/// When a collision occurs with another PhysicsObject, this
/// method gets called on both objects, with the other object
/// passed as its one parameter
/// 
/// This is a virtual method intended to be over-ridden by
/// a child class with object specific behavior
/// </summary>
void PhysicsObject::CollidedWith(PhysicsObject& otherObject)
{
#if DEBUG_COLLISION

	cout << "Obj of type ";
	PrintObjectTypeName();
	cout << " collided with obj of type ";
	otherObject.PrintObjectTypeName();
	cout << endl;

#endif // DEBUG_COLLISION
}

/// <summary>
/// Box2D has a coordinate system that is generally incompatible with a
/// pixel coordinate system as its scale is 1.0 = 1m.  To get anything but
/// very slow movement, the positions must be scaled to something where 1.0 is
/// much smaller.  This function returns the position of the physics body appropriately
/// scaled down
/// </summary>
/// <returns> A position for the center of the physics body scaled for pixel coordinates</returns>
Vector2f PhysicsObject::GetScaledCenterPosition()
{
	b2Vec2 pos = body->GetPosition();
	return Vector2f(pos.x * boxScaleFactor, pos.y * boxScaleFactor);
}

/// <summary>
/// This is the reverse of GetScaledPosition.  It sets the physics bodies position
/// to an identically scaled up version of the pixel position
/// </summary>
/// <param name="pos">The pixel position of the center of the scaled body</param>
/// <summary>
void PhysicsObject::SetScaledCenterPosition(Vector2f pos)
{
	b2Vec2 bPos = b2Vec2(pos.x / boxScaleFactor,pos.y / boxScaleFactor);
	body->SetTransform(bPos, 0);
}

///  This returns a normalized vector that represents the current direction of motion of
///  the phsyics body.
/// </summary>
/// <returns> A normalized vector indicating the current direction of motion</returns>
Vector2f PhysicsObject::GetMotionDirection()
{
	b2Vec2 dir = body->GetLinearVelocity();
	dir.Normalize();
	return Vector2f(dir.x, dir.y);
}

/// <summary>
/// This applies a force to the physics body at the same scale as the set and get scaled
/// position calls
/// </summary>
/// <param name="forceVector">The force to apply scaled in pixel coordinates</param>
void PhysicsObject::ApplyScaledForce(Vector2f forceVector)
{
	b2Vec2 scaledForce(forceVector.x * boxScaleFactor, forceVector.y * boxScaleFactor);
	body->ApplyForce(scaledForce, body->GetPosition(),true);
}