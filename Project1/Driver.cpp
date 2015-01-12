/*
*TODO: 
*   1. Make a 'in game object' parent class to use for bricks, powerups, etc.
*      It will contain information about sprites, state, etc.
*   2. Create a fileformat to allow for easily imputted levels
*/
#include "Input.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Database.h"
#include "GLTools.h"
#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
class Ball;

// The main menu
Menu menu;
// Game mode
bool singlePlayer;


int main(void)
{

	if (GLTools::GLFWInit(Input::key_callback) < 0){
		return -1;
	}

	GLTools::GLInit();

	// Show the menu before getting to the game
	// Right now, single and two player modes enter single player mode
	// idea: Keep ONE main loop; the only thing that changes when using
	//       single player mode is how commands are inputted to player 2
	menu = Menu();
	switch (menu.displayMenu()){
	case -1:
		GLTools::VAOcleanup();
		glfwTerminate();
		return 0;
	case 0:
		singlePlayer = true;	
		break;
	case 1:
		singlePlayer = false;
		break;
	}
	Database db = Database(singlePlayer);

	// Main game loop
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Check if any events (eg. key presses) have happened
		glfwPollEvents();

		db.processKeyPresses();
		db.processCollisions();
		db.moveBalls();

		// If playing one player mode, move the AI
		if (singlePlayer){
			db.cpuMove();
		}

		GLTools::enableVAO();
		
		// render the players
		for (Player &player : db.getPlayers()){
			if (Input::debug){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			GLTools::renderRectangle(&player);
		}

		// render the balls
		for (Ball &ball : db.getBalls()){
			GLTools::renderRectangle(&ball);
		}

		// render the bricks
		std::list<Brick> list = db.getBricks();
		std::list<Brick>::iterator iterator = list.begin();
		while (iterator != list.end()){

			GLTools::renderRectangle(&(*iterator));

			iterator++;
		}
		
		// Swap buffers
		glfwSwapBuffers(GLTools::window);

		// Go back to the menu
		if (Input::keysPressed[KEY_ESC]){
			switch (menu.displayMenu()){
			case -1:
				glfwSetWindowShouldClose(GLTools::window, GL_TRUE);
			case 0:
				singlePlayer = true;
				db.resetSinglePlayer();
				break;
			case 1:
				singlePlayer = false;
				db.resetTwoPlayer();
				break;
			}
		}

	} // Check if the ESC key was pressed or the window was closed
	while (!glfwWindowShouldClose(GLTools::window));

	GLTools::VAOcleanup();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}