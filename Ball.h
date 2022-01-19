#pragma once
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "PhysicsObject.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Sound.hpp"

using namespace sf;

/// <summary>
/// This class represents the ball on the screen.  It extends the SFML CircleShape for drawing and PhysicsObject
/// for motion and collision
/// </summary>
class Ball :
    public CircleShape, public PhysicsObject
{
private:
    /// <summary>
    /// Whether the ball is currently being displayed
    /// </summary>
    bool visible;
    /// <summary>
    /// A sound for when it hits a block
    /// </summary>
    SoundBuffer beep;
    /// <summary>
    /// A sound for when it hits a wall
    /// </summary>
    SoundBuffer boop;
    /// <summary>
    /// A sound for when it exits the bottom of the screen
    /// </summary>
    SoundBuffer drain;
    /// <summary>
    /// An SFML sound object that actually hanldes the play of the above sounds
    /// </summary>
    Sound sound; // used to play a buffer


public:
    /// <summary>
    /// Ball object constructor
    /// </summary>
    /// <param name="world">A reference to the Box2D world that owns all our physics objects</param>
    /// <param name="radius">The radius of the ball in pixels</param>
    /// <param name="startPosition">The position of the center of the ball on the playign field</param>
    Ball(b2World& world,float radius, Vector2f startPosition );
    /// <summary>
    /// Called to update the ball's position for a new frame.  Position is controlled
    /// by its Box2D physics body
    /// </summary>
    void Update();
    /// <summary>
    /// Sets the ball active and visible (true) or inactive and invisible (false)
    /// </summary>
    /// <param name="b">true if active and visible, false if not</param>
    void Show(bool b);
    /// <summary>
    /// Gets the last value set with Show
    /// </summary>
    /// <returns>true if active and visible, false if not</returns>
    bool IsVisible();
    /// <summary>
    /// Positions the ball and resets its initial movement vector
    /// </summary>
    /// <param name="position">where the center of the ball shoudl be in pixel coords</param>
    /// <param name="angleDeg">the angle of starting motion</param>
    /// <param name="speed">the speed of starting motion</param>
    void Reset(Vector2f position, float angleDeg,float speed);
    /// <summary>
    /// Called by the physics system when the ball collides with another PhysicsObject
    /// </summary>
    /// <param name="otherObject"></param>
    void CollidedWith(PhysicsObject& otherObject);
};

