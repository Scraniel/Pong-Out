#ifndef BALL_H
#define BALL_H

#include "Rectangle.h"	
class Player;

// x and y coordinates are for the top left corner
class Ball : public Rectangle {
	bool moveUp, moveDown, moveLeft, moveRight, attached;
	Player * lastHit;
public:
	Ball(float, float, float, float, glm::vec3 colour, Player *);
	// Consider moving this up to Rectangle if the ball class inherits from it.
	// Alternatively, create another parent class that deals with movement, and
	// have both the ball and player inherit it. This way we can place the move
	// function, dx, dy, and all the move booleans there as well. 
	void move();
};

#endif