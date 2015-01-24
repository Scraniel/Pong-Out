#include "Menu.h"

Menu::Menu()
{
	// 1 player mode button
	mainMenuButtons[0] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0, 150, 50, GREEN);

	// 2 player mode
	mainMenuButtons[1] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0 - 75, 150, 50, RED);

	// Settings
	mainMenuButtons[2] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0 - 150, 150, 50, RED);

	// Exit
	mainMenuButtons[3] = Rectangle(W_WIDTH / 2.0 - 75, W_HEIGHT / 2.0 - 225, 150, 50, RED);

	// in Game menu panel
	inGameMenuPanel = Rectangle(W_WIDTH / 2.0 - 100, W_HEIGHT / 2.0 + 150, 200, 250, BLUE);

	// in Game menu buttons
	inGameMenuButtons[0] = Rectangle(inGameMenuPanel.getX() + 25, inGameMenuPanel.getY() - (inGameMenuPanel.getHeight() * (1.0 / 5.0)), 150, 50, GREEN);
	inGameMenuButtons[1] = Rectangle(inGameMenuPanel.getX() + 25, inGameMenuPanel.getY() - (inGameMenuPanel.getHeight() * (3.0 / 5.0)), 150, 50, RED);
	
	selected = ONE_PLAYER;
}

// Draws the menu and enters the 'menu' loop, which will exit once the player decides to play the game
// returns 0 for single player, 1 for 2 player, and -1 to exit.
int Menu::displayMenu()
{
	bool onePlayer = false;
	
	// Reset buttons to default state (top button selected, the rest not)
	selected = ONE_PLAYER;
	mainMenuButtons[0].setColour(GREEN);
	for (int i = 1; i < 4; i++){
		mainMenuButtons[i].setColour(RED);
	}

	while (!onePlayer){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		GLTools::enableVAO();

		for (Rectangle &button : mainMenuButtons){
			GLTools::renderRectangle(&button);
		}

		glfwSwapBuffers(GLTools::window);

		// Changing menu selection
		if (Input::keysPressed[KEY_DOWN]){
			if (selected != EXIT){
				mainMenuButtons[selected].setColour(RED);
				mainMenuButtons[++selected].setColour(GREEN);
				Input::keysPressed[KEY_DOWN] = false;
			}
		}
		if (Input::keysPressed[KEY_UP]){
			if (selected != ONE_PLAYER){
				mainMenuButtons[selected].setColour(RED);
				mainMenuButtons[--selected].setColour(GREEN);
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

int Menu::inGameMenu(){
	bool resumeGame = false;
	// Reset buttons to default state (top button selected, the rest not)
	selected = RESUME;
	inGameMenuButtons[0].setColour(GREEN);
	inGameMenuButtons[1].setColour(RED);

	while (!resumeGame){

		// glScissor creates a box, and when the scissor test is enabled, only pixels in that box can be modified. Thus, clearing the screen only clears that box.
		glScissor(inGameMenuPanel.getX(),								// Bottom left corner X
			      inGameMenuPanel.getY() - inGameMenuPanel.getHeight(), // Bottom left corner Y (my rectangles are specified by top left, so have to decrease by box's height)
				  inGameMenuPanel.getWidth(),							// Width
				  inGameMenuPanel.getHeight());							// Height
		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // (or whatever buffer you want to clear)
		glDisable(GL_SCISSOR_TEST);

		glfwPollEvents();

		GLTools::enableVAO();
		
		for (Rectangle &button : inGameMenuButtons){
			GLTools::renderRectangle(&button);
		}
		

		GLTools::renderRectangle(&inGameMenuPanel);
		glfwSwapBuffers(GLTools::window);

		// Changing menu selection
		
		if (Input::keysPressed[KEY_DOWN]){
			if (selected != MAIN_MENU){
				inGameMenuButtons[selected].setColour(RED);
				inGameMenuButtons[++selected].setColour(GREEN);
				Input::keysPressed[KEY_DOWN] = false;
			}
		}
		if (Input::keysPressed[KEY_UP]){
			if (selected != RESUME){
				inGameMenuButtons[selected].setColour(RED);
				inGameMenuButtons[--selected].setColour(GREEN);
				Input::keysPressed[KEY_UP] = false;
			}
		}

		// Choosing menu selection
		if (Input::keysPressed[KEY_ENTER]){
			Input::keysPressed[KEY_ENTER] = false;   // This is so single player mode isn't immediately entered when going back to the menu.
			switch (selected){
			case RESUME:
				return 0;
			case MAIN_MENU:
				return 1;
			}
		}
	}
}
