#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.h"

/// <summary>
/// This is a class that represents a boundary on the side of the screen
/// It is a static Box2D object (does not itelf move) but it does participate
/// in collision with the ball.  It inherites RectangleShape from SFMl for drawing
/// itself and PhysicsObject to particpate in the Box2D physics
/// </summary>
class Boundary :
    public RectangleShape,public PhysicsObject
{
public:
    /// <summary>
    /// This is the constructor for a Boundary object
    /// </summary>
    /// <param name="world">A reference to the Box2D physics world it partcipates in</param>
    /// <param name="color">The color of the drawn rectangle</param>
    /// <param name="position">The top left corner of the drawn rectangle</param>
    /// <param name="size">The size of both the drawn rectangle and the rectangular physics body</param>
    Boundary(b2World& world,Color color, Vector2f position, Vector2f size);
};

