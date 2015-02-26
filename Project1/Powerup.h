#pragma once
#include "Rectangle.h"
#include "Player.h"
class Powerup : public Rectangle {
	bool destroy;
	int type;
public:
	Powerup(float, float, int, int, GLuint);
	void move();
	void collide(Player *);
	bool hitWall();
};

