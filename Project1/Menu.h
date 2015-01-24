#pragma once
#include "GLTools.h"
#include "Input.h"
#include "Rectangle.h"
class Menu
{
	Rectangle mainMenuButtons[4];
	Rectangle inGameMenuButtons[2];
	Rectangle inGameMenuPanel;
	short selected;
public:
	Menu();
	// Draws the menu and enters the 'menu' loop, which will exit once the player decides to play the game	
	int displayMenu();
	// Displays the score screen, which gives the player the option to go back to the main menu or exit
	void displayScore(int, int);
	int inGameMenu();
};

