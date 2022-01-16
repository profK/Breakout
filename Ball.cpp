#define _USE_MATH_DEFINES // gets us M_PI from Math.h
#include "Ball.h"
#include "Box2D.h"
#include <math.h>
#include "PhysicsObject.h"


Ball::Ball(b2World& world, float radius, Vector2f startPosition): CircleShape(radius),
	PhysicsObject(world,BallType,startPosition,Vector2f(radius*2,radius*2)),
	radius(radius)
{
	visible = true; // start showing ball
	setRotation(30);
}

void Ball::Update()
{
	Vector2f pos = GetScaledPosition();
	setPosition(pos);
}

void Ball::Show(bool b)
{
	visible = b;
}

bool Ball::IsVisible()
{
	return visible;
}

void Ball::CollidedWith(PhysicsObject& otherObject){
	if (otherObject.GetObjType() == BrickType) {
		//increase speed
		Vector2f direction = GetMotionDirection();
		Vector2f force(direction.x * 0.01, direction.y * 0.01);
		ApplyScaledForce(force);
	}
}

void Ball::Reset(Vector2f position, float angleDeg, float speed) 
{
	setPosition(position);
	b2Vec2 impulse = b2Vec2(cos(angleDeg * M_PI / 180), sin(angleDeg * M_PI / 180));
	impulse *= speed;
	SetScaledPosition(position);
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(),true);
}

