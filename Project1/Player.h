#ifndef PLAYER_H
#define PLAYER_H

#include "Rectangle.h"
class Ball;


// x and y coordinates are for the top left corner
class Player : public Rectangle {
	short movementKeys[4];
	bool moveUp, moveDown, moveLeft, moveRight;
	Ball * ball;
	int score;
public:
	Player(float, float, float, float, glm::vec3 colour, short, short, short, short, Ball *);
	Player();
	// Consider moving this up to Rectangle if the ball class inherits from it.
	// Alternatively, create another parent class that deals with movement, and
	// have both the ball and player inherit it. This way we can place the move
	// function, dx, dy, and all the move booleans there as well. 
	void move();
	void setMovementKeys(short, short, short, short);
	short* getMovementKeys();
};

#endif