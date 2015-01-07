#ifndef PLAYER_H
#define PLAYER_H

#include "Rectangle.h"
class Ball;

// x and y coordinates are for the top left corner
class Player : public Rectangle {
	short movementKeys[5], id;
	bool moveUp, moveDown, moveLeft, moveRight;
	Ball * ball[2];
	int score;
public:
	Player(float, float, float, float, glm::vec3 colour, short, short, short, short, short, short, Ball *);
	Player();
	// Consider moving this up to Rectangle if the ball class inherits from it.
	// Alternatively, create another parent class that deals with movement, and
	// have both the ball and player inherit it. This way we can place the move
	// function, dx, dy, and all the move booleans there as well. 
	void move();
	// Sets the movement keys. Each key is defined in Constants.h
	void setMovementKeys(short, short, short, short);
	short* getMovementKeys();
	// Returns the player ID for determining which side the player is on (right
	// now with 2 players, P1 is on the left and P2 is on the right)
	short getId();
	// Increases score by 1. Could add a win condition for points that is checked
	// here. Could also pass a parameter in to increase score by differing amounts
	// if scored on vs if a brick is destroyed
	void incScore();
	// Decreases score by 1. Has a floor of 0. 
	void decScore();
	// Reurns the score
	short getScore();
	// Gets a pointer to the first ball in the players list of held (attached) balls
	// without removing it from the list
	Ball * getBall();
	// Adds a ball to the player's list of balls. setBall(null) is the same as popBall()
	// without returning the ball
	void setBall(Ball *);
	// Gets a pointer to the first ball in the players list of held (attached) balls
	// and removes it from the list
	Ball * popBall();
	// Returns an array containing which CPU keys to set in Input::keysPressed[];
	// logic of the AI. Returns an array of size 5
	bool * cpuMove(Ball[], short);

};

#endif