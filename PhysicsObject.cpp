#include "PhysicsObject.h"

using namespace sf;

PhysicsObject::PhysicsObject(b2World& world, ObjectType otype, Vector2f startPosition, Vector2f size):
	world(world)
{
	
	objType = otype;
	// setup phsics
	b2BodyDef bodyDef;
	if (otype == BallType) {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(startPosition.x, startPosition.y);
	bodyDef.linearDamping = 0.0f;

	body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x,size.y);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 1.0f;
	fixtureDef.friction = 0;
	fixtureDef.userData = this;
	body->CreateFixture(&fixtureDef);
}

ObjectType PhysicsObject::GetObjType()
{
	return objType;
}
