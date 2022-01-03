#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Brick : public RectangleShape
{

public:
	Brick(Color color, Vector2f size, Vector2f position);
};

