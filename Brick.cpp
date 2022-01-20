#include "Brick.h"
#include "Box2D.h"
#include "Score.h"


/// <summary>
/// A constructor for an on-screen brick object
/// </summary>
/// <param name="world">A reference to the physics world this object participates in</param>
/// <param name="score">A reference to the Score object</param>
/// <param name="color">The color of the brick</param>
/// <param name="size">The width and hight of the brick</param>
/// <param name="position">the top left corner of the brick in pixel coordinates</param>
Brick::Brick(b2World& world, Score &score, Color color, Vector2f position, Vector2f size) :
	PhysicsObject(world, BrickType, position, size),
	score(score)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
	
}

/// <summary>
/// THis method is called by the game when a brick collides with another PhysicsObject
/// </summary>
/// <param name="otherObject">The object that collided with the brick</param>
void Brick::CollidedWith(PhysicsObject& otherObject)
{
	destroyNode = true;
	score.SetScore(score.GetScore() + 3);
}

/// <summary>
/// This is the update procedure to be called one a frame.
/// Its most important function is that it adds itself to the removal
/// list if destroyNode has been set to true
/// </summary>
/// <param name="removalList">A reference to a list to be added to if destoryNode is true</param>
void Brick::Update(list<Brick*> &removalList)
{
	if (destroyNode) {
		removalList.push_back(this);
		world.DestroyBody(body);
	}
}
