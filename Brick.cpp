#include "Brick.h"
#include "Box2D.h"
#include "Score.h"


Brick::Brick(b2World& world, Score &score, Color color, Vector2f position, Vector2f size) :
	PhysicsObject(world, BrickType, position, size),
	score(score)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
	
}

void Brick::CollidedWith(PhysicsObject& otherObject)
{
	destroyNode = true;
	score.SetScore(score.GetScore() + 3);
}

void Brick::Update(list<Brick*> &removalList)
{
	if (destroyNode) {
		removalList.push_back(this);
		world.DestroyBody(body);
	}
}
