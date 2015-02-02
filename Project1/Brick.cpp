#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, glm::vec3 colour, bool hasPowerup, int lives) : Rectangle(x, y, width, height, colour){
	this->powerup = hasPowerup;
	this->lives = lives;
}

bool Brick::hasPowerup(){
	return this->powerup;
}