#define _USE_MATH_DEFINES // gets us M_PI from Math.h
#include "Ball.h"
#include "Box2D.h"
#include <math.h>



Ball::Ball(b2World& world, float radius, Vector2f startPosition):CircleShape(radius)
{

	// setup phsics
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(startPosition.x,startPosition.y);
	body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(radius*2, radius*2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	visible = true; // start showing ball
}

void Ball::Update()
{
	const b2Vec2& pos = body->GetPosition();
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

