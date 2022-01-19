#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include <list>
#include "Score.h"

using namespace sf;
using namespace std;

/// <summary>
/// This class represents a brick on screen.  It inherits RectangleShape from SFML to
/// draw itself and Physics object in order to participatein collisions
/// </summary>
class Brick : public RectangleShape, public PhysicsObject
{

private:
	/// <summary>
	/// This is a reference to the Score object so it can add points when
	/// the brick is destroyed.
	/// </summary>
	Score &score;
	/// <summary>
	/// Trying to destroy the brick in the middle of a collision would leave nasty dangling
	/// pointers to deallocated memory.  Instead, a ball collision sets this flag true
	/// which is then read to destroy the ball at the appropriate time
	/// </summary>
	bool destroyNode = false;

public:
	/// <summary>
	/// A constructor for an on-screen brick object
	/// </summary>
	/// <param name="world">A reference to the physics world this object participates in</param>
	/// <param name="score">A reference to the Score object</param>
	/// <param name="color">The color of the brick</param>
	/// <param name="size">The width and hight of the brick</param>
	/// <param name="position">the top left corner of the brick in pixel coordinates</param>
	Brick(b2World& world, Score &score,  Color color, Vector2f size, Vector2f position);
	/// <summary>
	/// THis method is called by the game when a brick collides with another PhysicsObject
	/// </summary>
	/// <param name="otherObject">The object that collided with the brick</param>
	void CollidedWith(PhysicsObject& otherObject);
	/// <summary>
	/// This is the update procedure to be called one a frame.
	/// Its most important function is that it adds itself to the removal
	/// list if destroyNode has been set to true
	/// </summary>
	/// <param name="removalList">A reference to a list to be added to if destoryNode is true</param>
	void Update(list<Brick*>& removalList);
};

