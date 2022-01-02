#include "Gun.h"

Gun::Gun(Vector2f startingPos)
{
	float points[8][2] = {
		{0,0},
		{0,-10},
		{10,-10},
		{10,-20},
		{15,-20},
		{15,-10},
		{25,-10},
		{25,0}
	};
	setPointCount(8);
	for (int i = 0; i < 8; i++) {
		setPoint(i, Vector2f(points[i][0],points[i][1]));
	}
	setPosition(startingPos);
}
