#include "ShootMessage.h"

/// <summary>
/// This is a convenience object for drawing the "Press space bar..." message
/// It know how yo psotion itself on screen.
/// Otherwise its just a 
/// </summary>
/// <param name="fnt"></param>
/// <param name="screenWidth"></param>
/// <param name="screenHeight"></param>
ShootMessage::ShootMessage(Font &fnt, int screenWidth, int screenHeight)
{
	setFont(fnt);
	setString(" Press space to launch a ball");
	setPosition((screenWidth-getGlobalBounds().width) / 2, screenHeight *.8);
}
