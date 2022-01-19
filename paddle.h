#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "PhysicsObject.h"

using namespace sf;
using namespace std;

const float movePPS = 0.5;

/// <summary>
/// This class represents the player controlled paddle.  It particpates in Box2D collision
/// but hadles its own motion.  (such asn object is commonly called a "kinematic" object)
/// it inherits from SFMl RectangleShape to handle drawing
/// </summary>
class Paddle : public PhysicsObject,
    public RectangleShape
{
public:
	/// <summary>
	/// The paddle object constructor
	/// </summary>
	/// <param name="world">A reference to the Box2D Physics World it participates in</param>
	/// <param name="color">The color of the rectangle</param>
	/// <param name="size">The width and height of the rectangle</param>
	/// <param name="position">The starting top left corner of the paddle</param>
	Paddle(b2World& world, Color color, Vector2f size, Vector2f position);
	/// <summary>
	/// THis method is called by the game when a paddle collides with another PhysicsObject
	/// </summary>
	/// <param name="otherObject">The object that collided with the paddle</param>
	void CollidedWith(PhysicsObject& otherObject);
	/// <summary>
	/// This is called once per frame to update the paddle's position
	/// as well as its associated physics body's position.
	/// It scales the motion by the elapsed time since last frame to ensure smooth
	/// movement
	/// </summary>
	/// <param name="deltaTime">the elapsed time since last frame in milliseconds</param>
	void Update(long deltaTime);
};

