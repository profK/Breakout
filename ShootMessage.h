#pragma once
#include "SFML/Graphics/Text.hpp"

using namespace sf;

class ShootMessage :public Text
{
public:
    ShootMessage(Font &fnt, int screenWidth, int screenHeight);
};