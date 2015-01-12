#include "Input.h"
bool Input::keysPressed[17];
bool Input::debug = false;

// callback function for pressing keys. Right now, it sets the respective locations in an
// array that gets checked every time in the main loop. This way, we can set keys in the
// player classes that do certain things. For example, each player has a 'movement' array
// that contains which locations in the main 'keys pressed' array to check (ie. If player
// 1 has 'W' set as his 'Up' movement key, just check the main 'keys pressed' array at
// KEY_W (0)).
void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		keysPressed[KEY_ESC] = true;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
		keysPressed[KEY_ESC] = false;
	}

	// Player 1 (For now. eventually, input will just set the boolean for every key on the keyboard,
	// and the driver will decide which ones to check)
	if (key == GLFW_KEY_W && (action == GLFW_PRESS)){
		keysPressed[KEY_W] = true;
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS)){
		keysPressed[KEY_S] = true;
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS)){
		keysPressed[KEY_D] = true;
	}
	if (key == GLFW_KEY_A && (action == GLFW_PRESS)){
		keysPressed[KEY_A] = true;
	}
	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS)){
		keysPressed[SPACEBAR] = true;
	}
	if (key == GLFW_KEY_W && (action == GLFW_RELEASE)){
		keysPressed[KEY_W] = false;
	}
	if (key == GLFW_KEY_S && (action == GLFW_RELEASE)){
		keysPressed[KEY_S] = false;
	}
	if (key == GLFW_KEY_D && (action == GLFW_RELEASE)){
		keysPressed[KEY_D] = false;
	}
	if (key == GLFW_KEY_A && (action == GLFW_RELEASE)){
		keysPressed[KEY_A] = false;
	}

	// player 2
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS)){
		keysPressed[KEY_UP] = true;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS)){
		keysPressed[KEY_DOWN] = true;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS)){
		keysPressed[KEY_RIGHT] = true;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS)){
		keysPressed[KEY_LEFT] = true;
	}
	if (key == GLFW_KEY_RIGHT_CONTROL && (action == GLFW_PRESS)){
		keysPressed[R_CTRL] = true;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_RELEASE)){
		keysPressed[KEY_UP] = false;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_RELEASE)){
	keysPressed[KEY_DOWN] = false;
	}
	if (key == GLFW_KEY_RIGHT && (action == GLFW_RELEASE)){
		keysPressed[KEY_RIGHT] = false;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_RELEASE)){
		keysPressed[KEY_LEFT] = false;
	}

	// Misc. (ie. no attachment to player)
	if (key == GLFW_KEY_ENTER && (action == GLFW_PRESS)){
		keysPressed[KEY_ENTER] = true;
	}
	if (key == GLFW_KEY_ENTER && (action == GLFW_RELEASE)){
		keysPressed[KEY_ENTER] = false;
	}

	// Debugging
	if (key == GLFW_KEY_GRAVE_ACCENT && (action == GLFW_PRESS)){
		if (debug == true){
			debug = false;
		}
		else{
			debug = true;
		}
	}
}