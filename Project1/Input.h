#ifndef INPUT_H
#define INPUT_H

#include "stdglincludes.h"
#include "Constants.h"

// Need a better way of using these two semi-globally (perhaps in the DB?)
class Input{

public:
	static bool keysPressed[16];
	static bool debug;
	static void key_callback(GLFWwindow*, int, int, int, int);
};

#endif