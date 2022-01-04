#include "Boundary.h"

Boundary::Boundary(b2World& world, Color color, Vector2f position, Vector2f size):
	PhysicsObject(world,WallType,position,size)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
}
