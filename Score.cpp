#include "Score.h"

Score::Score(Vector2f position, Font &fnt, int size)
{
	setFont(fnt);
	//setCharacterSize(size);
	setFillColor(Color::White);
	setStyle(Text::Bold);
    _position = position;
	SetScore(0);
	
}

void Score::SetScore(int score)
{
	_score = score;
	char scoreText[4];
	sprintf_s(scoreText, "%03d", score);
	setString(scoreText);
	float width = getLocalBounds().width;
	setPosition(_position.x - (width / 2), _position.y);
}

int Score::GetScore()
{
	return _score;
}
