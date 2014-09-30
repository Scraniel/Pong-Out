#include "stdglincludes.h"

bool keysPressed[8];

// callback function for pressing keys.
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Player 1
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS)){
		keysPressed[0] = true;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS)){
		keysPressed[1] = true;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS)){
		//keysPressed[2] = true;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS)){
		//keysPressed[3] = true;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_RELEASE)){
		keysPressed[0] = false;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_RELEASE)){
		keysPressed[1] = false;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_RELEASE)){
		//keysPressed[2] = false;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_RELEASE)){
		//keysPressed[3] = false;
	}

	// player 2
	if (key == GLFW_KEY_W && (action == GLFW_PRESS)){
		keysPressed[4] = true;
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS)){
		keysPressed[5] = true;
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS)){
		//keysPressed[6] = true;
	}
	if (key == GLFW_KEY_A && (action == GLFW_PRESS)){
		//keysPressed[7] = true;
	}
	if (key == GLFW_KEY_W && (action == GLFW_RELEASE)){
		keysPressed[4] = false;
	}
	if (key == GLFW_KEY_S && (action == GLFW_RELEASE)){
		keysPressed[5] = false;
	}
	if (key == GLFW_KEY_D && (action == GLFW_RELEASE)){
		//keysPressed[6] = false;
	}
	if (key == GLFW_KEY_A && (action == GLFW_RELEASE)){
		//keysPressed[7] = false;
	}

}