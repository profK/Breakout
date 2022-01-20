#include "paddle.h"

/// <summary>
/// The paddle object constructor
/// </summary>
/// <param name="world">A reference to the Box2D Physics World it participates in</param>
/// <param name="color">The color of the rectangle</param>
/// <param name="size">The width and height of the rectangle</param>
/// <param name="position">The starting top left corner of the paddle</param>
///
/// </summay>
/// 
Paddle::Paddle(b2World& world, Color color, Vector2f pos, Vector2f size):
	PhysicsObject(world, PaddleType,pos, size)
{
	setFillColor(color);
	setSize(size);
	setPosition(pos);
}

/// THis method is called by the game when a paddle collides with another PhysicsObject
/// </summary>
/// <param name="otherObject">The object that collided with the paddle</param>
void Paddle::CollidedWith(PhysicsObject& otherObject)
{
    //nop right now
}

/// <summary>
/// This is called once per frame to update the paddle's position
/// as well as its associated physics body's position.
/// It scales the motion by the elapsed time since last frame to ensure smooth
/// movement
/// </summary>
/// <param name="deltaTime">the elapsed time since last frame in milliseconds</param>
void Paddle::Update(long deltaTime)
{
    //read left and right arrow keys
    bool leftArrow = Keyboard::isKeyPressed(Keyboard::Left);
    bool rightArrow = Keyboard::isKeyPressed(Keyboard::Right);
    
    // check for just one of them pressed and set the new position
    // position is scaled by the time from last frame to keep motion even
    if (leftArrow && !rightArrow) {
        setPosition(getPosition() + Vector2f(-movePPS * deltaTime, 0));
    }
    if (rightArrow && !leftArrow) {
        setPosition(getPosition() + Vector2f(movePPS * deltaTime, 0));
    }
    // Now get the current SFML position and convert it to center coordinates
    // to set the Box2D position
    Vector2f sfmlPos = getPosition();
    Vector2f sfmlSize = getSize();

    SetScaledCenterPosition(Vector2f(sfmlPos.x + (sfmlSize.x/2), sfmlPos.y + (sfmlSize.y/2)));
}
