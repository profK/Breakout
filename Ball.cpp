#define _USE_MATH_DEFINES // gets us M_PI from Math.h
#include "Ball.h"
#include "Box2D.h"
#include <math.h>
#include "PhysicsObject.h"


Ball::Ball(b2World& world, float radius, Vector2f startPosition): CircleShape(radius),
	PhysicsObject(world,BallType,startPosition,Vector2f(radius*2,radius*2)),
	radius(radius)
{
	visible = false; // start not showing ball
	setRotation(30);
	//load audio
	beep.loadFromFile("audio/beep.wav");
	boop.loadFromFile("audio/boop.wav");
	drain.loadFromFile("audio/balldrain.wav");
}

void Ball::Update()
{
	Vector2f pos = GetScaledCenterPosition();
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

void Ball::CollidedWith(PhysicsObject& otherObject) {
	if (IsVisible()) { // no actions if deactivated}
		Vector2f direction = GetMotionDirection();
		Vector2f force(direction.x * 0.01, direction.y * 0.01);
		switch (otherObject.GetObjType()) {
		case BrickType:
			//increase speed	
			ApplyScaledForce(force);
			sound.setBuffer(beep);
			sound.play();
			break;
		case WallType:
		case PaddleType:
			sound.setBuffer(boop);
			sound.play();
			break;
		case ExitType:
			visible = false;
			body->SetLinearVelocity(b2Vec2(0, 0));
			sound.setBuffer(drain);
			sound.play();
		}
	}
	
}

void Ball::Reset(Vector2f position, float angleDeg, float speed) 
{
	setPosition(position);
	b2Vec2 impulse = b2Vec2(cos(angleDeg * M_PI / 180), sin(angleDeg * M_PI / 180));
	impulse *= speed;
	SetScaledCenterPosition(position);
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(),true);

}

