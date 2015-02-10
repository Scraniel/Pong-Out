#include "Rectangle.h"
#include <stdio.h>

Rectangle::Rectangle(float x, float y, float width, float height, glm::vec3 colour){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dx = 0;
	this->dy = 0;
	this->colour = colour;
	this->hitBottom = false;
	this->hitTop = false;
	this->hitLeft = false;
	this->hitRight = false;
	this->texturePath = BRICK_TEXTURE;

	// need to implement scaling based on width and height
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3((x / (W_WIDTH * 0.5)) - 1, (y / (W_HEIGHT * 0.5)) - 1, 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now
	
	this->model = translate * rotate * scale;
		
}

Rectangle::Rectangle(){}

void Rectangle::setWidth(float width){
	this->width = width;
}

void Rectangle::setHeight(float height){
	this->height = height;
}

float Rectangle::getWidth(){
	return this->width;
}

float Rectangle::getHeight(){
	return this->height;
}

void Rectangle::setX(float x){
	this->x = x;
	// Each of these matrices probably isn't necessary. Just need to figure out which locations to
	// set in the matrix
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3((x / (W_WIDTH * 0.5)) - 1, (y / (W_HEIGHT * 0.5)) - 1, 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now

	this->model = translate * rotate * scale;
}

void Rectangle::setY(float y){
	this->y = y;
	// Each of these matrices probably isn't necessary. Just need to figure out which locations to
	// set in the matrix.
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3((x / (W_WIDTH * 0.5)) - 1, (y / (W_HEIGHT * 0.5)) - 1, 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now

	this->model = translate * rotate * scale;
}

float Rectangle::getX(){
	return this->x;
}

float Rectangle::getY(){
	return this->y;
}

void Rectangle::setModel(glm::mat4 model){
	this->model = model;
}

glm::mat4 Rectangle::getModel(){
	return this->model;
}

void Rectangle::setdY(float dy){
	this->dy = dy;
}

void Rectangle::setdX(float dx){
	this->dx = dx;
}

float Rectangle::getdX(){
	return this->dx;
}

float Rectangle::getdY(){
	return this->dy;
}

glm::vec3 Rectangle::getColour(){
	return this->colour;
}

void Rectangle::setColour(glm::vec3 colour){
	this->colour = colour;
}

// Determines which side of the rectangle was hit, then sets the 'hit'
// flags in the rectangle. 
void Rectangle::collide(Rectangle * object){
	float xDirection, yDirection;
	float ballCenterX = (this->getX() + (this->getWidth() / 2.0));
	float playerCenterX = (object->getX() + (object->getWidth() / 2.0));
	float ballCenterY = (this->getY() - (this->getHeight() / 2.0));
	float playerCenterY = (object->getY() - (object->getHeight() / 2.0));

	// Minkowski sum. Helps determine which side the collision happened on. 
	float w = 0.5 * (this->getWidth() + object->getWidth());
	float h = 0.5 * (this->getHeight() + object->getHeight());
	float dx = ballCenterX - playerCenterX;
	float dy = ballCenterY - playerCenterY;
	float wy = w * dy;
	float hx = h * dx;

	if ((wy > hx) && (wy > -hx)){
		/* collision at the top */
		this->hitTop = true;
	}
	else if (!(wy > hx) && !(wy > -hx)){
		/* at the bottom */
		this->hitBottom = true;
	}
	else if ((wy > hx) && !(wy > -hx)){
		/* on the left */
		this->hitLeft = true;
	}
	
	else if(!(wy > hx) && (wy > -hx)){
		/* on the right */
		this->hitRight = true;
	}
	
}

void Rectangle::setTexturePath(const char * texturePath){
	this->texturePath = texturePath;
}

const char * Rectangle::getTexturePath(){
	return texturePath;
}