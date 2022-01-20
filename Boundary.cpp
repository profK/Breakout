#include "Boundary.h"

/// <summary>
/// This is the constructor for a Boundary object
/// </summary>
/// <param name="world">A reference to the Box2D physics world it partcipates in</param>
/// <param name="color">The color of the drawn rectangle</param>
/// <param name="position">The top left corner of the drawn rectangle</param>
/// <param name="size">The size of both the drawn rectangle and the rectangular physics body</param>
Boundary::Boundary(b2World& world, Color color, Vector2f position, Vector2f size):
	PhysicsObject(world,WallType,position+Vector2f(size.x/2,size.y/2),size)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
}
