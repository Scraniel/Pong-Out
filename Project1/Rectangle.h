#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"
extern short W_WIDTH_NO_BORDER;
extern short W_HEIGHT_NO_BORDER;


// x and y coordinates are for the top left corner
class Rectangle {
protected:
	float width, height, x, y;
	glm::mat4 model;
public:
	Rectangle(float, float, float, float);
	void setWidth(float);
	void setHeight(float);
	void setX(float);
	void setY(float);
	void setModel(glm::mat4);
	float getWidth();
	float getHeight();
	float getX();
	float getY();
	glm::mat4 getModel();

};
#endif