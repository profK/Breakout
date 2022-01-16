#pragma once
#include "Box2D.h"
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;

enum ObjectType {
	BallType, WallType, BrickType,PaddleType,ExitType
};




class PhysicsObject
{
	
public:
	b2World& world;
	b2Body* body;
	ObjectType objType;

	PhysicsObject(b2World& world, ObjectType otype, Vector2f startPosition, Vector2f size);
	ObjectType GetObjType();
	void PrintObjectTypeName();
	virtual void CollidedWith(PhysicsObject& otherObject);
	Vector2f GetScaledPosition();
	void SetScaledPosition(Vector2f pos);
	Vector2f GetMotionDirection();
	void ApplyScaledForce(Vector2f forceVector);

};

