#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"
#include <vector>
#include "stdglincludes.h"
extern short W_WIDTH_NO_BORDER;
extern short W_HEIGHT_NO_BORDER;


// x and y coordinates are for the top left corner
// Should hold sprite info in here as well
class Rectangle {
protected:
	bool hitTop, hitBottom, hitLeft, hitRight;
	float width, height, x, y, dx, dy;
	glm::mat4 model;
	glm::vec3 colour;
	const char * texturePath; // may not be necessary with the textureSampler GLuint
	GLuint textureSampler;
public:
	Rectangle(float, float, float, float, glm::vec3, GLuint);
	Rectangle();
	void setWidth(float);
	void setHeight(float);
	void setX(float);
	void setY(float);
	void setModel(glm::mat4);
	float getWidth();
	float getHeight();
	float getX();
	float getY();
	void setdX(float);
	void setdY(float);
	float getdX();
	float getdY();
	glm::mat4 getModel();
	glm::vec3 getColour();
	void Rectangle::setColour(glm::vec3);
	// Generic, overridable collide function for rectangles. Basically just
	// sets the correct 'hit' boolean value based on what side of the rectangle
	// was hit.
	virtual void collide(Rectangle*);
	void setTexturePath(const char *);
	const char * getTexturePath(); // may not be necessary with the textureSampler GLuint

	GLuint getTextureSampler();
	void setTextureSampler(GLuint);

};

#endif
