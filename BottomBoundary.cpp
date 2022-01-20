#include "BottomBoundary.h"


/// <summary>
/// A constructor for BottomBoundary
/// </summary>
/// <param name="world">See Boundary.h</param>
/// <param name="color">See Boundary.h</param>
/// <param name="position">See Boundary.h</param>
/// <param name="size">See Boundary.h</param>
BottomBoundary::BottomBoundary(b2World& world, Color color, Vector2f position, Vector2f size):
	Boundary(world,color,position,size)
{
	this->objType = ExitType;
}
