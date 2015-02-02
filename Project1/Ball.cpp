// TODO: add launching from paddles functionality
// TODO: add collision function (to collide with paddles, bricks, and balls)

#include "Ball.h"
#include <stdio.h>


Ball::Ball(float x, float y, float width, float height, glm::vec3 colour, Player * attachedTo) : Rectangle(x, y, width, height, colour){
	this->dx = BALL_START_DX;
	this->dy = BALL_START_DY;
	this->attached = true;
	this->lastHit = attachedTo;
	this->remove = false;
}
Ball::Ball(){}

// Helper function
void Ball::attachToPaddle(float * xOffset, float * yOffset){

	*yOffset = - (this->lastHit->getHeight() / 2.0) + (this->width / 2.0);

	if (this->lastHit->getId() == 1){
		*xOffset = this->lastHit->getWidth();
	}
	else{
		*xOffset = -this->lastHit->getWidth();
	}

	this->attached = true;
	this->lastHit->setBall(this);	
}

// Colliding with walls will be done in here. Need to create a 'Collide' function that
// checks all objects in a given area for collision, then changes dx / dy based on that. 
void Ball::move(){
	float newY, newX, xOffset, yOffset;

	newY = this->y + this->dy;
	newX = this->x + this->dx;

	if (!attached){
	
		// This is sort of hacky
		if (newY > W_HEIGHT){
			newY = W_HEIGHT;
			dy = -dy;
		}
		if (newY - this->height < 0){
			newY = this->height;
			dy = -dy;
		}
				
		// Ball goes off screen; attach to your paddle and score
		if (newX + this->width > W_WIDTH){
			attachToPaddle(&xOffset, &yOffset);

			newX = this->lastHit->getX() + xOffset;
			newY = this->lastHit->getY() + yOffset;
	
			// Score on opponent
			if (this->lastHit->getId() == 1){
				this->lastHit->incScore();
			}
			// Score on self	
			else{
				if (this->lastHit->getScore() > 0){
					this->lastHit->decScore();
				}
			}
		}
		else if (newX < 0){

			attachToPaddle(&xOffset, &yOffset);

			newX = this->lastHit->getX() + xOffset;
			newY = this->lastHit->getY() + yOffset;
	
			// Score on opponent
			if (this->lastHit->getId() == 2){
				this->lastHit->incScore();
			}
			// Score on self
			else{
				if (this->lastHit->getScore() > 0){
					this->lastHit->decScore();
				}
			}
		}
	}

	this->setX(newX);
	this->setY(newY);
}

void Ball::setLastHit(Player * player){
	this->lastHit = player;
}

void Ball::generalCollide(Rectangle * object) {
	// Determines which side was hit
	Rectangle::collide(object);
	int xDirection, yDirection;

	if (this->hitTop){
		/* collision at the top */
		this->hitTop = false;
		this->setdY(-this->getdY());
		this->setdX(-this->getdX());
		xDirection = 0;
		yDirection = 1;
		fprintf(stderr, "Hit the top!\n");
	}
	else if (this->hitLeft){
		/* on the left */
		this->hitLeft = false;
		this->setdX(-this->getdX());
		xDirection = -1;
		yDirection = 0;
		fprintf(stderr, "Hit the left!\n");
	}
		
	else if (this->hitRight){
		/* on the right */
		this->hitRight = false;
		this->setdX(-this->getdX());
		xDirection = 1;
		yDirection = 0;
		fprintf(stderr, "Hit the right!\n");
	}
	// Revisit later. Still possible for the ball to get stuck
	else if (this->hitBottom){
		/* at the bottom */
		this->hitBottom = false;
		this->setdY(-this->getdY());
		this->setdX(-this->getdX());
		xDirection = 0;
		yDirection = -1;
		fprintf(stderr, "Hit the bottom!\n");
	}
	
	
	// move the ball a small amount in the correct direciton, so the ball doesn't get
	// stuck in the player / brick
	this->setX(this->getX() + xDirection * 10.0);
	this->setY(this->getY() + yDirection * 10.0);

}

// Specific collide functions for players / bricks
void Ball::collide(Player * player){
	generalCollide(player);

	// Set up information about which player was hit
	this->setLastHit(player);
	this->setColour(player->getColour());
}

void Ball::collide(Brick * brick){
	generalCollide(brick);

	// Set up information about which player hit the brick
	this->lastHit->incScore();
}

void Ball::setAttached(bool attached){
	this->attached = attached;
}

bool Ball::isAttached(){
	return this->attached;
}

void Ball::reset(){
	float xOffset, yOffset;
	attachToPaddle(&xOffset, &yOffset);

	this->setX(this->lastHit->getX() + xOffset);
	this->setY(this->lastHit->getY() + yOffset);
	this->setAttached(true);
}

int Ball::lastHitID(){
	return this->lastHit->getId();
}