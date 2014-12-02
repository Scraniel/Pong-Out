#include "Database.h"
#include "Ball.h"
// This class will eventually hold all of the object information. All other
// classes that need to access these objects will query the Database. For 
// right now, all it holds is the 'Collide' function.


/*
* An idea for this function: Determine if the two rectangles collide, and
* that's IT. Each object will have its own 'collide' function that determines
* what happens. This way, this function can be called in the main for everything,
* and all the different cases (ie. ball hitting ball, ball hitting paddle, ball
* hitting brick) will all be accounted for. 
* 
* TODO: make a 'In game object' class that is inherited by ball and powerup.
*/
bool Database::collide(Ball * one, Rectangle * two){
	// One is to the left of two
	if (one->getX() + one->getWidth() < two->getX()){
		return false;
	}
	// One is to the right of two
	if (one->getX() > two->getX() + two->getWidth()){
		return false;
	}
	// One is above two
	if (one->getY() - one->getHeight() > two->getY()){
		return false;
	}
	// One is below two
	if (one->getY() < two->getY() - two->getHeight()){
		return false;
	}
	
	return true;
}