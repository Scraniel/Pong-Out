#ifndef DATABASE_H
#define DATABASE_H
#include "Ball.h"
#include "Input.h"
#include <list>
#include <vector>

class Database{
	std::vector<Player> players;
	std::vector<Ball> balls;
	// Making a linked list so arbitrary element deletion is efficient
	std::list<Brick> bricks;
	int currentLoop = 0;
private:
	// Right now only works with rectangles. If we add other things, 
	// (such as triangles, circles, etc.) make an 'object' super class. 
	bool collide(Ball * one, Rectangle * two);
	// Deletes the bricks, and re-fills them back to default
	void resetBricks();
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
	// processes collisions for bricks and players
	void processCollisions();
	// updates players based on input
	void processKeyPresses();
	// updates ball positions
	void moveBalls();
	// moves the computer player (AI)
	void cpuMove();
};

#endif