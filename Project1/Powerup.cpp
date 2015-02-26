#include "Powerup.h"


Powerup::Powerup(float x, float y, int direction, int type, GLuint textureSampler) : Rectangle(x, y, 20, 20, ORANGE, textureSampler) {
	this->destroy = false;
	this->dx = direction * POWERUP_SPEED;
	this->type = type;
}

void Powerup::collide(Player * player){
	
	// Give player powerup
	//
	//

	player->startPowerup(this->type);
	
}

void Powerup::move(){

	float newX;

	newX = this->x + this->dx;

	// Powerup goes off screen, destroy it
	if (newX + this->width > W_WIDTH){
		this->destroy = true;
	}
	else if (newX < 0){
		this->destroy = true;
	}
	

	this->setX(newX);
}

bool Powerup::hitWall(){
	return this->destroy;
}