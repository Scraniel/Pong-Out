#ifndef PLAYER_H
#define PLAYER_H

#include "Rectangle.h"


// x and y coordinates are for the top left corner
class Player : public Rectangle {
	short movementKeys[4];
	float dx, dy;
	bool moveUp, moveDown, moveLeft, moveRight;
public:
	Player(float, float, float, float, short, short, short, short);
	// Consider moving this up to Rectangle if the ball class inherits from it.
	// Alternatively, create another parent class that deals with movement, and
	// have both the ball and player inherit it. This way we can place the move
	// function, dx, dy, and all the move booleans there as well. 
	void move();
	void setdX(float);
	void setdY(float);
	void setMovementKeys(short, short, short, short);
	float getdX();
	float getdY();
	short* getMovementKeys();
};

#endif