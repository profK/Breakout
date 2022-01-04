#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.h"

class Boundary :
    public RectangleShape,public PhysicsObject
{
public:
    Boundary(b2World& world,Color color, Vector2f position, Vector2f size);
};

