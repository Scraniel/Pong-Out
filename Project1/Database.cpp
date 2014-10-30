#include "Database.h"
// This class will eventually hold all of the object information. All other
// classes that need to access these objects will query the Database. For 
// right now, all it holds is the 'Collide' function.

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

	one->setdX(0 - one->getdX());
}