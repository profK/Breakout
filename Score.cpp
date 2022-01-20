#include "Score.h"

/// <summary>
/// The constructor for the Score object
/// </summary>
/// <param name="position">The position of the center of the text on screen</param>
/// <param name="fnt">A reference to the font object to use to render the score text</param>
Score::Score(Vector2f position, Font &fnt)
{
	setFont(fnt);
	//setCharacterSize(size);
	setFillColor(Color::White);
	setStyle(Text::Bold);
    _position = position;
	SetScore(0);
	
}

/// <summary>
/// Set the value of the score state
/// This also recalculates the screen position to keep it centered on the
/// set position regardless of he text width
/// </summary>
/// <param name="score">the new score value</param>
void Score::SetScore(int score)
{
	_score = score;
	char scoreText[4];
	sprintf_s(scoreText, "%03d", score);
	setString(scoreText);
	float width = getLocalBounds().width;
	setPosition(_position.x - (width / 2), _position.y);
}

/// <summary>
/// get the current value of the score state
/// </summary>
/// <returns>the current score value</returns>
int Score::GetScore()
{
	return _score;
}
