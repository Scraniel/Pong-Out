#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"

// x and y coordinates are for the top left corner
class Rectangle {
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