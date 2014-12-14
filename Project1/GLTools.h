#pragma once

#include "Rectangle.h"
#include "stdglincludes.h"
#include <stdio.h>

// Contains various methods to initialize and use the openGL functionality
// such as rendering a rectangle (and later other shapes)
class GLTools
{
	// Private members and functions are used as helpers / data that does
	// not need to be known elsewhere in the program
	static GLuint vertexBuffer, colourBuffer, programID, vertexArrayID;
	static GLfloat vertexData [];
private:
	static void bindVAOs(Rectangle *);
	static void reloadMVPUniform(Rectangle *);
	static void generateVAOs();
	static void setupVAOs();
	
	// Public functions are the initialization / rendering functions
public:
	// Right now used in the driver to swap buffers
	static GLFWwindow * window;
	// Initializes OpenGL (ie. creates and binds VAOs)
	static void GLInit();
	// Renders the rectangle passed in to the window context
	static void renderRectangle(Rectangle *);
	// Called before rendering a Rectangle (may be able to move it in this class)
	static void enableVAO();
	// Destroys the buffers created by GLInit
	static void VAOcleanup();
	// Inizializes GLFW for window context / keyboard input
	static int GLFWInit(GLFWkeyfun);
};

