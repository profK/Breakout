#pragma once
#include "Boundary.h"
class BottomBoundary :
    public Boundary
{
public:
    BottomBoundary(b2World& world, Color color, Vector2f position, Vector2f size);
};

