#include "Menu.h"

Menu::Menu()
{
	// 1 player mode button
	buttons[0] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0, 150, 50, GREEN);

	// 2 player mode
	buttons[1] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0 - 75, 150, 50, RED);

	// Settings
	buttons[2] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0 - 150, 150, 50, RED);

	// Exit
	buttons[3] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0 - 225, 150, 50, RED);

	selected = ONE_PLAYER;
}

// Draws the menu and enters the 'menu' loop, which will exit once the player decides to play the game
// returns 0 for single player, 1 for 2 player, and -1 to exit.
int Menu::displayMenu()
{
	bool onePlayer = false;

	while (!onePlayer){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		GLTools::enableVAO();

		for (Rectangle &button : buttons){
			GLTools::renderRectangle(&button);
		}

		glfwSwapBuffers(GLTools::window);

		// Changing menu selection
		if (Input::keysPressed[KEY_DOWN]){
			if (selected != EXIT){
				buttons[selected].setColour(RED);
				buttons[++selected].setColour(GREEN);
				Input::keysPressed[KEY_DOWN] = false;
			}
		}
		if (Input::keysPressed[KEY_UP]){
			if (selected != ONE_PLAYER){
				buttons[selected].setColour(RED);
				buttons[--selected].setColour(GREEN);
				Input::keysPressed[KEY_UP] = false;
			}
		}

		// Choosing menu selection
		if (Input::keysPressed[KEY_ENTER]){
			switch (selected){
			case ONE_PLAYER:
				return 0;
			case TWO_PLAYER:
				return 1;
			case SETTINGS:
				break;
			case EXIT:
				return -1;
			}
		}
	}
}
