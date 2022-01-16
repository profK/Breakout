#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include <list>
#include "Score.h"

using namespace sf;
using namespace std;

class Brick : public RectangleShape, public PhysicsObject
{

private:
	Score &score;
	bool destroyNode = false;

public:
	Brick(b2World& world, Score &score,  Color color, Vector2f size, Vector2f position);
	void CollidedWith(PhysicsObject& otherObject);
	void Update(list<Brick*>& removalList);
};

