#include "Database.h"
// This class will eventually hold all of the object information. All other
// classes that need to access these objects will query the Database. For 
// right now, all it holds is the 'Collide' function.


/*
* An idea for this function: Determine if the two rectangles collide, and
* that's IT. Each object will have its own 'collide' function that determines
* what happens. This way, this function can be called in the main for everything,
* and all the different cases (ie. ball hitting ball, ball hitting paddle, ball
* hitting brick) will all be accounted for. 
*/
void Database::collide(Rectangle * one, Rectangle * two){
	// One is to the left of two
	if (one->getX() + one->getWidth() < two->getX()){
		return;
	}
	// One is to the right of two
	if (one->getX() > two->getX() + two->getWidth()){
		return;
	}
	// One is above two
	if (one->getY() - one->getHeight() > two->getY()){
		return;
	}
	// One is below two
	if (one->getY() < two->getY() - two->getHeight()){
		return;
	}
	// If the ball is moving down and on the top half or up and on the bottom half, switch direction of y
	if ((one->getY() > two->getY() - (two->getHeight() / 2)) && one->getdY() < 0){
		one->setdY( -one->getdY());
	}
	

	one->setdX(-one->getdX());
	one->setColour(two->getColour());
}