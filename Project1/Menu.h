#pragma once
#include "GLTools.h"
#include "Input.h"
#include "Rectangle.h"

/*
 * Consider making a 'menu panel' class which holds buttons. This way we can create a generic method which auto
 * places the buttons at a pre-defined place in the panel as opposed to manually placing rectangles inside another
 * rectangle. 
 */
class Menu
{
	Rectangle mainMenuButtons[4];
	Rectangle inGameMenuButtons[2];
	Rectangle inGameMenuPanel;
	short selected;
	GLuint selectedTex[4];
	GLuint unselectedTex[4];
	GLuint inGameSelectedTex[2];
	GLuint inGameUnselectedTex[2];
public:
	Menu();
	// Draws the menu and enters the 'menu' loop, which will exit once the player decides to play the game	
	int displayMenu();
	// Displays the score screen, which gives the player the option to go back to the main menu or exit
	void displayScore(int, int);
	// Displays the ingame menu, which overlays the game screen. Can resume game or go back to menu
	int inGameMenu();
};

