#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"

using namespace std;
using namespace sf;

/// <summary>
/// This class represents the score displayed on screen.
/// Its is just an SFMl Text object extended with numeric
/// state.  It does not participate in the physics world.
/// </summary>
class Score : public Text
{
private:
	/// <summary>
	/// The state of the score, which begins at zero
	/// </summary>
	int _score = 0;
	/// <summary>
	/// The position of the center of the text.
	/// This is stored so screen position can be recalculated
	/// to keep it centered when the text changes
	/// </summary>
	Vector2f _position;
	
public:
	/// <summary>
	/// The constructor for the Score object
	/// </summary>
	/// <param name="position">The position of the center of the text on screen</param>
	/// <param name="fnt">A reference to the font object to use to render the score text</param>
	Score(Vector2f position, Font &fnt);
	/// <summary>
	/// Set the value of the score state
	/// </summary>
	/// <param name="score">the new score value</param>
	void SetScore(int score);
	/// <summary>
	/// get the current value of the score state
	/// </summary>
	/// <returns>the current score value</returns>
	int GetScore();
	

};

