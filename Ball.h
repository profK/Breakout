#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.h"

using namespace sf;

class Ball :
    public CircleShape, public PhysicsObject
{
private:
    float radius;
    bool visible;


public:
    Ball(b2World& world,float radius, Vector2f startPosition );
    void Update();
    void Show(bool b);
    bool IsVisible();
    void Reset(Vector2f position, float angleDeg,float speed);
    void CollidedWith(PhysicsObject& otherObject);
};

