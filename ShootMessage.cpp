#include "ShootMessage.h"

/// <summary>
/// The constructor
/// </summary>
/// <param name="fnt">A reference to a font to use to draw the text</param>
/// <param name="screenWidth">width of the screen</param>
/// <param name="screenHeight">height of the screen</param>
ShootMessage::ShootMessage(Font &fnt, int screenWidth, int screenHeight)
{
	setFont(fnt);
	setString(" Press space to launch a ball");
	setPosition((screenWidth-getGlobalBounds().width) / 2, screenHeight *.8);
}
