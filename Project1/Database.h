#ifndef DATABASE_H
#define DATABASE_H
#include "Ball.h"

class Database{
public:
	// Right now only works with rectangles. If we add other things, 
	// Make an 'object' super class. 
	static bool collide(Ball * one, Rectangle * two);
};

#endif