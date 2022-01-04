#include "Brick.h"
#include "Box2D.h"

Brick::Brick(b2World& world, Color color, Vector2f size, Vector2f position):
	PhysicsObject(world, BrickType, size, position)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
	
}
