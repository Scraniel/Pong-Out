#ifndef BRICK_H
#define BRICK_H

#include "Rectangle.h"

class Brick : public Rectangle{
	bool remove, powerup;
	int lives;
public:
	Brick(float, float, float, float, glm::vec3, bool, int);
	bool hasPowerup();
}; 

#endif // !BRICK_H