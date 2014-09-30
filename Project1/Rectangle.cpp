#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, float width, float height){
	Rectangle::x = x;
	Rectangle::y = y;
	Rectangle::width = width;
	Rectangle::height = height;

	// need to implement scaling based on width and height
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3(x / (W_WIDTH * 0.5), y / (W_HEIGHT * 0.5), 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now
	
	Rectangle::model = translate * rotate * scale;
		
}

void Rectangle::setWidth(float width){
	Rectangle::width = width;
}

void Rectangle::setHeight(float height){
	Rectangle::height = height;
}

float Rectangle::getWidth(){
	return Rectangle::width;
}

float Rectangle::getHeight(){
	return Rectangle::height;
}

void Rectangle::setX(float x){
	Rectangle::x = x;
	// need to implement scaling based on width and height
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3(x / (W_WIDTH * 0.5), y / (W_HEIGHT * 0.5), 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now

	Rectangle::model = translate * rotate * scale;
}

void Rectangle::setY(float y){
	Rectangle::y = y;
	// need to implement scaling based on width and height
	glm::mat4 scale = glm::scale(glm::vec3(width / W_WIDTH, height / W_HEIGHT, 0.0));
	glm::mat4 translate = glm::translate(glm::vec3(x / (W_WIDTH * 0.5), y / (W_HEIGHT * 0.5), 0.0));
	glm::mat4 rotate = glm::mat4(); // identity matrix for now

	Rectangle::model = translate * rotate * scale;
}

float Rectangle::getX(){
	return Rectangle::x;
}

float Rectangle::getY(){
	return Rectangle::y;
}

void Rectangle::setModel(glm::mat4 model){
	Rectangle::model = model;
}

glm::mat4 Rectangle::getModel(){
	return Rectangle::model;
}