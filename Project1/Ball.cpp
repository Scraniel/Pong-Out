// TODO: add launching from paddles functionality
// TODO: add collision function (to collide with paddles, bricks, and balls)

#include "Ball.h"


Ball::Ball(float x, float y, float width, float height, glm::vec3 colour, Player * attachedTo) : Rectangle(x, y, width, height, colour){
	this->dx = 8;
	this->dy = 6;
	this->attached = true;
	this->lastHit = attachedTo;
}

// Colliding with walls will be done in here. Need to create a 'Collide' function that
// checks all objects in a given area for collision, then changes dx / dy based on that. 
void Ball::move(){
	float newY, newX;

	newY = this->y + this->dy;

	// This is sort of hacky
	if (newY > W_HEIGHT){
		newY = W_HEIGHT;
		dy = -dy;
	}
	else if (newY - this->height < 0){
		newY = this->height;
		dy = -dy;
	}
	this->setY(newY);

	newX = this->x + this->dx;
	if (newX + this->width > W_WIDTH){
		newX = W_WIDTH - this->width;
		dx = -dx;
	}
	else if (newX < 0){
		newX = 0;
		dx = -dx;
	}
	this->setX(newX);

}