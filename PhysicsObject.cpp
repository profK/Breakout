#include "PhysicsObject.h"
#include <iostream>
using namespace sf;
using namespace std;

const float boxScaleFactor= 100;

PhysicsObject::PhysicsObject(b2World& world, ObjectType otype, Vector2f centerPosition, Vector2f size):
	world(world)
{
	centerPosition /= boxScaleFactor;
	size /= boxScaleFactor;
	objType = otype;
	// setup phsics
	b2BodyDef bodyDef;
	if ((otype == BallType)||(otype == PaddleType)) {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(centerPosition.x+(size.x/2), centerPosition.y+(size.y/2));
	bodyDef.linearDamping = 0.0f;

	body = world.CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox(size.x/2,size.y/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 1.0f;
	fixtureDef.friction = 0;
	fixtureDef.userData = this;
	body->CreateFixture(&fixtureDef);
}

ObjectType PhysicsObject::GetObjType()
{
	return objType;
}

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


void PhysicsObject::CollidedWith(PhysicsObject& otherObject)
{
	cout << "Obj of type ";
	PrintObjectTypeName();
	cout << " collided with obj of type ";
	otherObject.PrintObjectTypeName();
	cout << endl;
}

Vector2f PhysicsObject::GetScaledCenterPosition()
{
	b2Vec2 pos = body->GetPosition();
	return Vector2f(pos.x * boxScaleFactor, pos.y * boxScaleFactor);
}

void PhysicsObject::SetScaledCenterPosition(Vector2f pos)
{
	b2Vec2 bPos = b2Vec2(pos.x / boxScaleFactor,pos.y / boxScaleFactor);
	body->SetTransform(bPos, 0);
}

Vector2f PhysicsObject::GetMotionDirection()
{
	b2Vec2 dir = body->GetLinearVelocity();
	dir.Normalize();
	return Vector2f(dir.x, dir.y);
}

void PhysicsObject::ApplyScaledForce(Vector2f forceVector)
{
	b2Vec2 scaledForce(forceVector.x * boxScaleFactor, forceVector.y * boxScaleFactor);
	body->ApplyForce(scaledForce, body->GetPosition(),true);
}