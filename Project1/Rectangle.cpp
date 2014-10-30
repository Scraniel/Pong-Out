#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float width, float height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->dx = 0;
	this->dy = 0;

	// need to implement scaling based on width and height
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3(x / (W_WIDTH * 0.5), y / (W_HEIGHT * 0.5), 0.0));
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
	glm::mat4 translate = glm::translate(glm::vec3(x / (W_WIDTH * 0.5), y / (W_HEIGHT * 0.5), 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now

	this->model = translate * rotate * scale;
}

void Rectangle::setY(float y){
	this->y = y;
	// Each of these matrices probably isn't necessary. Just need to figure out which locations to
	// set in the matrix.
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3(x / (W_WIDTH * 0.5), y / (W_HEIGHT * 0.5), 0.0));
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