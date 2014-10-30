#ifndef DATABASE_H
#define DATABASE_H
#include "Rectangle.h"

class Database{
public:
	// Right now only works with rectangles. If we add other things, 
	// Make an 'object' super class. 
	static void collide(Rectangle * one, Rectangle * two);
};

#endif