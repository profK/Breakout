#pragma once
#include "Box2D.h"
#include "SFML/Graphics.hpp"

using namespace sf;

enum ObjectType {
	BallType, WallType, BrickType,
};


class PhysicsObject
{
	
public:
	b2World& world;
	b2Body* body;
	ObjectType objType;
	PhysicsObject(b2World& world, ObjectType otype, Vector2f startPosition, Vector2f size);
	ObjectType GetObjType();

};

