#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "PhysicsObject.h"

using namespace sf;
using namespace std;

const float movePPS = 0.5;

class Paddle : public PhysicsObject,
    public RectangleShape
{
public:
	Paddle(b2World& world, Color color, Vector2f size, Vector2f position);
	void CollidedWith(PhysicsObject& otherObject);
	void Update(long deltaTime);
};

