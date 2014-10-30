// TODO: add launching from paddles functionality
// TODO: add collision function (to collide with paddles, bricks, and balls)

#include "Ball.h"


Ball::Ball(float x, float y, float width, float height, Player * attachedTo) : Rectangle(x, y, width, height){
	this->dx = 10;
	this->dy = 8;
	this->lastHit = attachedTo;
}

// Colliding with walls will be done in here. Need to create a 'Collide' function that
// checks all objects in a given area for collision, then changes dx / dy based on that. 
void Ball::move(){
	float newY, newX;

	newY = this->y + this->dy;

	// This is sort of hacky. For some reason
	if (newY > (W_HEIGHT - height) / 2.0){
		newY = (W_HEIGHT - height) / 2.0;
		dy = -dy;
	}
	else if (newY < ((W_HEIGHT - height) / 2.0)*(-1.0)){
		newY = ((W_HEIGHT - height) / 2.0)*(-1.0);
		dy = -dy;
	}
	this->setY(newY);

	newX = this->x + this->dx;
	if (newX >(W_WIDTH - height) / 2.0){
		newX = (W_WIDTH - height) / 2.0;
		dx = -dx;
	}
	else if (newX < ((W_WIDTH - height) / 2.0)*(-1.0)){
		newX = ((W_WIDTH - height) / 2.0)*(-1.0);
		dx = -dx;
	}
	this->setX(newX);

}