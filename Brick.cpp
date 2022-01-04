#include "Brick.h"
#include "Box2D.h"


Brick::Brick(b2World& world, list<Brick*> &actors, Color color, Vector2f position, Vector2f size):
	PhysicsObject(world, BrickType, position, size),
	actors(actors)
{
	setFillColor(color);
	setSize(size);
	setPosition(position);
	
}

void Brick::CollidedWith(PhysicsObject& otherObject)
{
	destroyNode = true;
}

void Brick::Update(list<Brick*> &removalList)
{
	if (destroyNode) {
		removalList.push_back(this);
		world.DestroyBody(body);
	}
}
