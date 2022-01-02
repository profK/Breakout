#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

using namespace sf;

class Ball :
    public CircleShape
{
private:
    
    b2Body* body;
    bool visible;

public:
    Ball(b2World& world,float radius, Vector2f startPosition);
    void Update();
    void Show(bool b);
    bool IsVisible();
    void Reset(Vector2f position, float angleDeg,float speed);
};

