#pragma once
#include "SFML/Graphics/Text.hpp"

using namespace sf;

/// <summary>
/// This is a convenience object for drawing the "Press space bar..." message
/// It know how yo psotion itself on screen.
/// Otherwise its just an SFML Text objet
/// </summary>
/// <param name="fnt">A reference to a font to use to draw the text</param>
/// <param name="screenWidth">width of the screen</param>
/// <param name="screenHeight">height of the screen</param>
class ShootMessage :public Text
{
public:
    /// <summary>
    /// The constructor
    /// </summary>
    /// <param name="fnt">A reference to a font to use to draw the text</param>
    /// <param name="screenWidth">width of the screen</param>
    /// <param name="screenHeight">height of the screen</param>
    ShootMessage(Font &fnt, int screenWidth, int screenHeight);
};