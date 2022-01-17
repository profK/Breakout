#include "ShootMessage.h"

ShootMessage::ShootMessage(Font &fnt, int screenWidth, int screenHeight)
{
	setFont(fnt);
	setString(" Press space to launch a ball");
	setPosition((screenWidth-getGlobalBounds().width) / 2, screenHeight *.8);
}
