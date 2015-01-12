#ifndef BALL_H
#define BALL_H

#include "Rectangle.h"
#include "Player.h"
#include "Brick.h"

// x and y coordinates are for the top left corner
class Ball : public Rectangle {
	bool moveUp, moveDown, moveLeft, moveRight, attached, remove;
	Player * lastHit;
	void attachToPaddle(float *, float *);
	void generalCollide(Rectangle *); 
public:
	Ball(float, float, float, float, glm::vec3 colour, Player *);
	Ball();
	// Consider moving this up to Rectangle if the ball class inherits from it.
	// Alternatively, create another parent class that deals with movement, and
	// have both the ball and player inherit it. This way we can place the move
	// function, dx, dy, and all the move booleans there as well. 
	void move();
	void setLastHit(Player *);
	// collide override for players
	void collide(Player *);
	// collide override for bricks
	void collide(Brick *);
	void setAttached(bool);
	// returns true if the ball is attached to a paddle
	bool isAttached();
	// returns the ball to its paddle, attaches it
	void reset();
};

#endif