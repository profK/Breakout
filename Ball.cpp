#define _USE_MATH_DEFINES // gets us M_PI from Math.h
#include "Ball.h"
#include "Box2D.h"
#include <math.h>
#include "PhysicsObject.h"




Ball::Ball(b2World& world, float radius, Vector2f startPosition): CircleShape(radius),
	PhysicsObject(world,BallType,startPosition,Vector2f(radius*2,radius*2))
{

	visible = true; // start showing ball
}

void Ball::Update()
{
	b2Vec2 pos(body->GetPosition());
	setPosition(Vector2f(pos.x, pos.y));
}

void Ball::Show(bool b)
{
	visible = b;
}

bool Ball::IsVisible()
{
	return visible;
}

void Ball::Reset(Vector2f position, float angleDeg, float speed)
{
	setPosition(position);
	b2Vec2 linearVelocity = b2Vec2(cos(angleDeg * M_PI / 180), sin(angleDeg * M_PI / 180));
	linearVelocity *= speed;
	body->SetLinearVelocity(linearVelocity);
	body->SetTransform(b2Vec2(position.x, position.y), 0);
}

