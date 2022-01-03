#include "Boundary.h"

Boundary::Boundary(b2World& world, Color color, Vector2f size, Vector2f position):
	PhysicsObject(world,WallType,size,position)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
}
