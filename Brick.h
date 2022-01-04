#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
using namespace sf;

class Brick : public RectangleShape, public PhysicsObject
{

public:
	Brick(b2World& world, Color color, Vector2f size, Vector2f position);
};

