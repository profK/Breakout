#include "BottomBoundary.h"

BottomBoundary::BottomBoundary(b2World& world, Color color, Vector2f position, Vector2f size):
	Boundary(world,color,position,size)
{
	this->objType = ExitType;
}
