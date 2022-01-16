#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Text.hpp"

using namespace std;
using namespace sf;

class Score : public Text
{
private:
	int _score = 0;
	Vector2f _position;
	
public:
	Score(Vector2f position, Font &fnt, int size);
	void SetScore(int score);
	int GetScore();
	

};

