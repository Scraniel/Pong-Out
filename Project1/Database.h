#ifndef DATABASE_H
#define DATABASE_H
#include "Ball.h"
#include "Input.h"
#include "Powerup.h"
#include <list>
#include <vector>
#include <glm/gtx/random.hpp>

class Database{
	std::vector<Player> players;
	std::vector<Ball> balls;
	// Making a linked list so arbitrary element deletion is efficient
	std::list<Brick> bricks;
	std::list<Powerup> powerups;
	int currentLoop = 0;
private:
	// Right now only works with rectangles. If we add other things, 
	// (such as triangles, circles, etc.) make an 'object' super class. 
	bool collide(Rectangle * one, Rectangle * two);
	// Deletes the bricks, and re-fills them back to default
	void resetBricks();
	// Generates a powerup and adds it to the list of powerups
	void generatePowerup(float, float, int);
public:
	Database(bool);
	// Sets the game (bricks, players) up for single player
	void resetSinglePlayer();
	// Sets the game (brings, players) up for two player
	void resetTwoPlayer();

	// Returns player array for rendering
	std::vector<Player> getPlayers();
	// Returns ball array for rendering
	std::vector<Ball> getBalls();
	// Returns brick list for rendering
	std::list<Brick> getBricks();
	// Returns powerup list for rendering
	std::list<Powerup> getPowerups();

	// processes collisions for bricks and players
	void processCollisions();
	// updates players based on input
	void processKeyPresses();
	// updates ball positions
	void moveBalls();
	// updates the computer player (AI)
	void cpuMove();
	// updates the powerups positions
	void movePowerups();
};

#endif