#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Sound.hpp"

using namespace sf;

class Ball :
    public CircleShape, public PhysicsObject
{
private:
    float radius;
    bool visible;
    SoundBuffer beep;
    SoundBuffer boop;
    SoundBuffer drain;
    Sound sound; // used to play a buffer


public:
    Ball(b2World& world,float radius, Vector2f startPosition );
    void Update();
    void Show(bool b);
    bool IsVisible();
    void Reset(Vector2f position, float angleDeg,float speed);
    void CollidedWith(PhysicsObject& otherObject);
};

