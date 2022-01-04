#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include <list>

using namespace sf;
using namespace std;

class Brick : public RectangleShape, public PhysicsObject
{

private:
	list<Brick*> &actors;
	bool destroyNode = false;

public:
	Brick(b2World& world, list<Brick*> &actors, Color color, Vector2f size, Vector2f position);
	void CollidedWith(PhysicsObject& otherObject);
	void Update(list<Brick*>& removalList);
};

