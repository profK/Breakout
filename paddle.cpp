#include "paddle.h"

Paddle::Paddle(b2World& world, Color color, Vector2f pos, Vector2f size):
	PhysicsObject(world, PaddleType,pos-Vector2f(size.x/2,size.y/2), size)
{
	setFillColor(color);
	setSize(size);
	setPosition(pos);
}

void Paddle::CollidedWith(PhysicsObject& otherObject)
{
    //nop right now
}

void Paddle::Update(long deltaTime)
{
    bool leftArrow = Keyboard::isKeyPressed(Keyboard::Left);
    bool rightArrow = Keyboard::isKeyPressed(Keyboard::Right);
    
    if (leftArrow && !rightArrow) {
        setPosition(getPosition() + Vector2f(-movePPS * deltaTime, 0));
    }
    if (rightArrow && !leftArrow) {
        setPosition(getPosition() + Vector2f(movePPS * deltaTime, 0));
    }
    Vector2f sfmlPos = getPosition();
    Vector2f sfmlSize = getSize();

    SetScaledPosition(Vector2f(sfmlPos.x + (sfmlSize.x/2), sfmlPos.y));
}
