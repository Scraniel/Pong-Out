#include "Input.h"

// callback function for pressing keys.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS)){
		keysPressed[0] = true;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS)){
		keysPressed[1] = true;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS)){
		keysPressed[2] = true;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS)){
		keysPressed[3] = true;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_RELEASE)){
		keysPressed[0] = false;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_RELEASE)){
		keysPressed[1] = false;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_RELEASE)){
		keysPressed[2] = false;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_RELEASE)){
		keysPressed[3] = false;
	}

}