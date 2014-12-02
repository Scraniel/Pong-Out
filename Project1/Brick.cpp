#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, glm::vec3 colour, bool hasPowerup, int lives) : Rectangle(x, y, width, height, colour){
	this->hasPowerup = hasPowerup;
	this->lives = lives;
}