#ifndef INPUT_H
#define INPUT_H

#include "stdglincludes.h"
#include "Constants.h"

// Consider moving input creation into the DB
class Input{

public:
	static bool keysPressed[17];
	static bool debug;
	static void key_callback(GLFWwindow*, int, int, int, int);
};

#endif