#include "Player.h"

Player::Player(float x, float y, float width, float height, short upKey, short downKey, short leftKey, short rightKey, Ball * ball) : Rectangle(x, y, width, height){
	this->movementKeys[MOVE_UP] = upKey;
	this->movementKeys[MOVE_DOWN] = downKey;
	this->movementKeys[MOVE_LEFT] = leftKey;
	this->movementKeys[MOVE_RIGHT] = rightKey;
	this->moveDown = false;
	this->moveUp = false;
	this->moveRight = false;
	this->moveLeft = false;
	this->ball = ball;
}

Player::Player(){}
// Currently no x logic because the paddles can only move up and down.
// TODO: make a 'collides' function to make it easier to work with collision with
//       balls / powerups
void Player::move(){
	float newY, newX;
	
	newY = this->y + this->dy;
	if (newY > (W_HEIGHT - height) / 2.0){
		newY = (W_HEIGHT - height) / 2.0;
	}
	else if (newY < ((W_HEIGHT - height) / 2.0)*(-1.0)){
		newY = ((W_HEIGHT - height) / 2.0)*(-1.0);
	}
	this->setY(newY);

	dy = 0;
}

short * Player::getMovementKeys(){
	return this->movementKeys;
}