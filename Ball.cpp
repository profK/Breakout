#define _USE_MATH_DEFINES // gets us M_PI from Math.h
#include "Ball.h"
#include "Box2D.h"
#include <math.h>
#include "PhysicsObject.h"


// see header file for docs
Ball::Ball(b2World& world, float radius, Vector2f startPosition): CircleShape(radius),
	PhysicsObject(world,BallType,startPosition,Vector2f(radius*2,radius*2))
{
	visible = false; // start not showing ball
	setRotation(30);
	//load audio
	// ball is in charge of playing sound effects on collision
	beep.loadFromFile("audio/beep.wav");
	boop.loadFromFile("audio/boop.wav");
	drain.loadFromFile("audio/balldrain.wav");
}

// see header file for docs
void Ball::Update()
{
	//This gets the position in piel coords from Box2D
	//and sets it in the CircleShape for drawing
	Vector2f pos = GetScaledCenterPosition();
	setPosition(pos);
}

// see header file for docs
void Ball::Show(bool b)
{
	visible = b;
}

// see header file for docs
bool Ball::IsVisible()
{
	return visible;
}

// see header file for docs
void Ball::CollidedWith(PhysicsObject& otherObject) {
	// if ball is invisible then its also inactive, so dont do any collision logic
	if (IsVisible()) { // no actions if deactivated
		//Brick collisions add some velocity by way of a force
		// the next 2 lines calculate that force
		Vector2f direction = GetMotionDirection();
		Vector2f force(direction.x * 0.01, direction.y * 0.01);
		switch (otherObject.GetObjType()) { //do differnt things depending on what we collided with
			case BrickType:  //collided with brick, increase velocity and play beep sound. Bounce is handled 
							 // for us by Box2D
							// removing the brick and adding to score is handled by the brick's 
				            // CollidedWith procedure	
				ApplyScaledForce(force);
				sound.setBuffer(beep);
				sound.play();
				break;
			case WallType: // collisions with wall and paddle do the same thing, boop and bounce
			case PaddleType:  // bounce is handled for us by Box2D
				sound.setBuffer(boop);
				sound.play();
				break;
			case ExitType: // collision woth the exit at bottom sets
						   // the ball inactive and plays drain noise
				visible = false;
				body->SetLinearVelocity(b2Vec2(0, 0));
				sound.setBuffer(drain);
				sound.play();
			}
	}
	
}

// see header file for docs
void Ball::Reset(Vector2f position, float angleDeg, float speed) 
{
	setPosition(position);
	// get a randomized starting direction
	b2Vec2 impulse = b2Vec2(cos(angleDeg * M_PI / 180), sin(angleDeg * M_PI / 180));
	impulse *= speed; // set the starting speed
	SetScaledCenterPosition(position); // put the ball physics bodyat the starting location
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(),true); // apply the starting force
}

