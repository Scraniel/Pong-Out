#include "Player.h"

Player::Player(float x, float y, float width, float height, glm::vec3 colour, short upKey, short downKey, short leftKey, short rightKey, Ball * ball) : Rectangle(x, y, width, height, colour){
	this->movementKeys[MOVE_UP] = upKey;
	this->movementKeys[MOVE_DOWN] = downKey;
	this->movementKeys[MOVE_LEFT] = leftKey;
	this->movementKeys[MOVE_RIGHT] = rightKey;
	this->moveDown = false;
	this->moveUp = false;
	this->moveRight = false;
	this->moveLeft = false;
	this->ball = ball;
	this->score = 0;
}

Player::Player(){}
// Currently no x logic because the paddles can only move up and down.
// TODO: make a 'collides' function to make it easier to work with collision with
//       balls / powerups
void Player::move(){
	float newY, newX;
	
	newY = this->y + this->dy;
	if (newY > W_HEIGHT){
		newY = W_HEIGHT;
	}
	else if (newY - this->getHeight() < 0){
		newY = this->getHeight();
	}
	this->setY(newY);

	dy = 0;
}

short * Player::getMovementKeys(){
	return this->movementKeys;
}