#include "Player.h"
#include "Ball.h"

//TODO: Change the balls list into a vector
Player::Player(float x, float y, float width, float height, glm::vec3 colour, short upKey, short downKey, short leftKey, short rightKey, short launchKey, short id, Ball * ball, GLuint textureSampler) : Rectangle(x, y, width, height, colour, textureSampler){
	this->setInputKeys(upKey, downKey, leftKey, rightKey, launchKey);
	// May need to do some refactoring when adding additional inputs (ie. AI / network players).
	// It may be better style to only set these when receiving input (but maybe not).
	this->moveDown = false;
	this->moveUp = false;
	this->moveRight = false;
	this->moveLeft = false;
	this->ball[0] = ball;
	this->ball[1] = NULL;
	this->score = 0;
	this->id = id;
	this->currentSpeed = PADDLE_SPEED_NORMAL;
	if (id == 2){
	//	this->rotation = 180; // rotation is not working correctly at the moment
	}
}

Player::Player(){}
// Currently no x logic because the paddles can only move up and down.
// TODO: make a 'collides' function to make it easier to work with collision with
//       balls / powerups
void Player::move(){
	float newY, newX;
	bool hitWall = false;
	
	newY = this->y + this->dy;
	if (newY > W_HEIGHT){
		newY = W_HEIGHT;
		hitWall = true;
	}
	else if (newY - this->getHeight() < 0){
		newY = this->getHeight();
		hitWall = true;
	}

	// If the paddle has at least one ball, go through each ball and move it. The
	// 'if (ball)' is for the (common) case where the paddle only has one ball, 
	// because for some stupid reason enhanced for loops count NULLs. 
	if (ball[0]){
		for (Ball * ball : ball){
			if (ball){
				if (hitWall){
					ball->setdX(0);
					ball->setdY(0);
				}
				else{
					ball->setdX(this->getdX());
					ball->setdY(this->getdY());
				}
			}
		}
	}

	this->setY(newY);
	this->dy = 0;
}

short * Player::getMovementKeys(){
	return this->movementKeys;
}

short Player::getId(){
	return this->id;	
}

void Player::incScore(){
	this->score++;
}

void Player::decScore(){
	this->score--;
}

short Player::getScore(){
	return this->score;
}

Ball * Player::getBall(){
	return this->ball[0];
}

Ball * Player::popBall(){
	Ball * returnBall = this->ball[0];

	this->ball[0] = this->ball[1];
	this->ball[1] = NULL;

	return returnBall;
}

// setBall adds the ball into the players list of balls.
// setBall(NULL) is the same as popBall(), without returning
// it. 
void Player::setBall(Ball * ball){
	
	if (!ball){
		this->ball[0] = this->ball[1];
		this->ball[1] = ball;
	}
	else if (this->ball[0]){
		this->ball[1] = ball;
	}
	else{
		this->ball[0] = ball;
	}
}

// using the location of the balls, determines where to move
// Right now, finds the closest ball, then moves up or down
// towards it. Also launches a ball as soon as it gets one
bool * Player::cpuMove(std::vector<Ball> balls){
	short numBalls = balls.size();
	bool keysToPress[5] = { false, false, false, false, false };
	Ball closestBall = balls[0];
	
	// Determine closest ball
	for (int i = 1; i < numBalls; i++){
		if (balls[i].getX() > closestBall.getX()){
			closestBall = balls[i];
		}
	}

	// Move towards it if it's on your half
	if (closestBall.getX() >= W_WIDTH / 2.0){
		if (closestBall.getY() <= this->getY() - this->getHeight()){
			keysToPress[CPU_DOWN - NUM_KEYBOARD_KEYS] = true;
		}
		else if (closestBall.getY() - closestBall.getHeight() >= this->getY()){
			keysToPress[CPU_UP - NUM_KEYBOARD_KEYS] = true;
		}

		// If you have a ball, launch it
		if (this->getBall()){
			keysToPress[CPU_LAUNCH - NUM_KEYBOARD_KEYS] = true;
		}
	}

	return keysToPress;
}

void Player::reset(){
	if (this->getId() == 2){
		this->setX(W_WIDTH - 100.0f);
		this->setY((W_HEIGHT / 2.0) + 50);
	}
	else{
		this->setX(100.0f);
		this->setY((W_HEIGHT / 2.0) + 50);
	}
	this->setScore(0);
	this->ball[0] = NULL;
	this->ball[1] = NULL;
}

void Player::setInputKeys(short upKey, short downKey, short leftKey, short rightKey, short launchKey){
	this->movementKeys[MOVE_UP] = upKey;
	this->movementKeys[MOVE_DOWN] = downKey;
	this->movementKeys[MOVE_LEFT] = leftKey;
	this->movementKeys[MOVE_RIGHT] = rightKey;
	this->movementKeys[LAUNCH_BALL] = launchKey;
}

void Player::setScore(int score){
	this->score = score;
}

void Player::startPowerup(int type){
	switch (type){
	case SPEED_UP:
		this->speedUp.startTimer();
		this->currentSpeed = PADDLE_SPEED_FAST;
		break;
	case SLOW_DOWN:
		this->slowDown.startTimer();
		this->currentSpeed = PADDLE_SPEED_SLOW;
		break;
	case MULTI_BALL:
		break;
	case BIGGER_PADDLE:
		this->biggerPaddle.startTimer();
		this->setHeight(PADDLE_LENGTH_LONG);
		break;
	}
}

void Player::stopPowerup(int type){
	switch (type){
	case SPEED_UP:
		this->speedUp.endTimer();
		this->currentSpeed = PADDLE_SPEED_NORMAL;
		break;
	case SLOW_DOWN:
		this->slowDown.endTimer();
		this->currentSpeed = PADDLE_SPEED_NORMAL;
		break;
	case MULTI_BALL:
		break;
	case BIGGER_PADDLE:
		this->biggerPaddle.endTimer();
		this->setHeight(PADDLE_LENGTH_NORMAL);
		break;
	}
}

int Player::getCurrentSpeed(){

	return this->currentSpeed;
}

void Player::checkPowerups(){
	if (speedUp.currentTime() >= POWERUP_TIME){
		this->stopPowerup(SPEED_UP);
	}
	if (slowDown.currentTime() >= POWERUP_TIME){
		this->stopPowerup(SLOW_DOWN);
	}
	if (multiBall.currentTime() >= POWERUP_TIME){
		this->stopPowerup(MULTI_BALL);
	}
	if (biggerPaddle.currentTime() >= POWERUP_TIME){
		this->stopPowerup(BIGGER_PADDLE);
	}
}

void Player::setBallTexture(GLuint ballTexture){
	this->ballTexture = ballTexture;
}

GLuint Player::getBallTexture(){
	return this->ballTexture;
}