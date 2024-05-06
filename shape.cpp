#include "shape.h"
#include "game.h"
#include "gameConfig.h"

shape::shape(game* r_pGame, point ref)
{
	RefPoint = ref;
	pGame = r_pGame;
	fillColor = config.fillColor;
	borderColor = config.penColor;
	flipped = false;
	rotated = 0;
}

void shape::setRefPoint(point p)
{
	RefPoint = p;
}
point shape::getRefPoint() {
	return RefPoint;
}




bool shape::GetFlipStatus() {
	return flipped;
}

