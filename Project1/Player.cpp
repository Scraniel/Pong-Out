#include "Player.h"

Player::Player(float x, float y, float width, float height, short upKey, short downKey, short leftKey, short rightKey) : Rectangle(x, y, width, height){
	this->movementKeys[MOVE_UP] = upKey;
	this->movementKeys[MOVE_DOWN] = downKey;
	this->movementKeys[MOVE_LEFT] = leftKey;
	this->movementKeys[MOVE_RIGHT] = rightKey;
	this->dx = 0;
	this->dy = 0;
	this->moveDown = false;
	this->moveUp = false;
	this->moveRight = false;
	this->moveLeft = false;
}

// Currently no x logic because the paddles can only move up and down. 
void Player::move(){
	float newY, newX;
	
	newY = this->y + this->dy;
	if (newY > W_HEIGHT_NO_BORDER / 2.0){
		newY = W_HEIGHT_NO_BORDER / 2.0;
	}
	else if (newY < (W_HEIGHT_NO_BORDER / 2.0)*(-1.0)){
		newY = (W_HEIGHT_NO_BORDER / 2.0)*(-1.0);
	}
	this->setY(newY);

	dy = 0;
}

short * Player::getMovementKeys(){
	return this->movementKeys;
}

void Player::setdY(float dy){
	this->dy = dy;
}