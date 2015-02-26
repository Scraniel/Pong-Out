#include "Database.h"
// This class will eventually hold all of the object information. All other
// classes that need to access these objects will query the Database.

Database::Database(bool singlePlayer){
	this->p1TextureSampler = GLTools::decodeLodePNG(PLAYER1_PADDLE);
	this->p2TextureSampler = GLTools::decodeLodePNG(PLAYER2_PADDLE);
	this->b1TextureSampler = GLTools::decodeLodePNG(PLAYER1_BALL);
	this->b2TextureSampler = GLTools::decodeLodePNG(PLAYER2_BALL);
	this->brickTextureSampler = GLTools::decodeLodePNG(BRICK_TEXTURE);
	this->speedUpSampler = GLTools::decodeLodePNG("Assets/Graphics/PowerUpRed.png");
	this->slowDownSampler = GLTools::decodeLodePNG("Assets/Graphics/PowerUpBlue.png");
	this->multiBallSampler = GLTools::decodeLodePNG("Assets/Graphics/PowerUpPink.png");
	this->bigPaddleSampler = GLTools::decodeLodePNG("Assets/Graphics/PowerUpGreen.png");

	Player newPlayer(100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, 100.0f, BLUE, KEY_W, KEY_S, KEY_A, KEY_D, SPACEBAR, 1, NULL, p1TextureSampler);
	newPlayer.setTexturePath(PLAYER1_PADDLE); // May not be necessary now
	newPlayer.setBallTexture(this->b1TextureSampler);
	players.push_back(newPlayer);

	if (singlePlayer){
		Player newPlayer(W_WIDTH - 100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, PADDLE_LENGTH_NORMAL, RED, CPU_UP, CPU_DOWN, CPU_LEFT, CPU_RIGHT, CPU_LAUNCH, 2, NULL, p2TextureSampler);
		newPlayer.setTexturePath(PLAYER2_PADDLE);
		newPlayer.setBallTexture(this->b2TextureSampler);
		players.push_back(newPlayer);
	}
	else{
		Player newPlayer(W_WIDTH - 100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, PADDLE_LENGTH_NORMAL, RED, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, R_CTRL, 2, NULL, p2TextureSampler);
		newPlayer.setTexturePath(PLAYER2_PADDLE);
		newPlayer.setBallTexture(this->b2TextureSampler);
		players.push_back(newPlayer);
	}

	Ball newBall1(players[0].getX() + players[0].getWidth(), players[0].getY() - (players[0].getHeight() / 2.0) + 12.5, 25.0f, 25.0f, players[0].getColour(), &players[0], b1TextureSampler);
	newBall1.setTexturePath(PLAYER1_BALL);
	balls.push_back(newBall1);

	Ball newBall2(players[1].getX() - players[1].getWidth(), players[1].getY() - (players[1].getHeight() / 2.0) + 12.5, 25.0f, 25.0f, players[1].getColour(), &players[1], b2TextureSampler);
	newBall2.setTexturePath(PLAYER2_BALL);
	balls.push_back(newBall2);

	// Set balls to be attached to players
	players[0].setBall(&balls[0]);
	players[1].setBall(&balls[1]);

	resetBricks();
}

void Database::resetBricks(){
	if (!bricks.empty()){
		bricks.clear();
	}
	/*
	* This should be moved into the input class so that levels can be specified
	* via a level file
	*/
	// Create bricks
	for (int i = 0; i < 14; i++){
		Brick newBrick((2 * W_WIDTH) / 5.0, W_HEIGHT - i*BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, GREEN, true, 1, this->brickTextureSampler);
		newBrick.setTexturePath(BRICK_TEXTURE);
		bricks.push_back(newBrick);
	}

	for (int i = 0; i < 14; i++){
		Brick newBrick((3 * W_WIDTH) / 5.0, W_HEIGHT - i*BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, GREEN, false, 1, this->brickTextureSampler);
		newBrick.setTexturePath(BRICK_TEXTURE);
		bricks.push_back(newBrick);
	}
}

/*
* An idea for this function: Determine if the two rectangles collide, and
* that's IT. Each object will have its own 'collide' function that determines
* what happens. This way, this function can be called in the main for everything,
* and all the different cases (ie. ball hitting ball, ball hitting paddle, ball
* hitting brick) will all be accounted for. 
* 
* TODO: make a 'In game object' class that is inherited by ball and powerup.
*/
bool Database::collide(Rectangle * one, Rectangle * two){
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

void Database::resetSinglePlayer(){

	for (int i = 0; i < 2; i++){
		players[i].reset();
		balls[i].setLastHit(&players[i]);
		balls[i].reset();
	}

	players[1].setInputKeys(CPU_UP, CPU_DOWN, CPU_LEFT, CPU_RIGHT, CPU_LAUNCH);
	resetBricks();
}

void Database::resetTwoPlayer(){
	for (int i = 0; i < 2; i++){
		players[i].reset();
		balls[i].setLastHit(&players[i]);
		balls[i].reset();
	}

	// This should be changed to be a file, as the player should be able to change input keys
	players[1].setInputKeys(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, R_CTRL);
	resetBricks();
}

std::vector<Player> Database::getPlayers(){
	return this->players;
}

std::vector<Ball> Database::getBalls(){
	return this->balls;
}

std::list<Brick> Database::getBricks(){
	return this->bricks;
}

std::list<Powerup> Database::getPowerups(){
	return this->powerups;
}

void Database::processCollisions(){
	// Ball collisions
	for (Ball &ball : this->balls){

		for (Player &player : this->players){
			if (Database::collide(&ball, &player) && !ball.isAttached()){
				ball.collide(&player);
			}
		}

		// Have to use this weird iterator while loop because of how the list class works
		// (eg. list.erase returns the next element, so we need a guard at the end to see
		// if the iterator has overstepped the bounds of the bricks list)
		std::list<Brick>::iterator iterator = this->bricks.begin();
		while (iterator != bricks.end()){
			bool collision = false;

			if (Database::collide(&ball, &(*iterator)) && !ball.isAttached()){
				collision = true;

				// if the ball has a powerup inside, generate one and add it to the list
				// of powerups
				if (iterator->hasPowerup()){
					int direction;
					if (ball.lastHitID() == 1){
						direction = LEFT;
					}
					else{
						direction = RIGHT;
					}

					generatePowerup(iterator->getX(), iterator->getY(), direction);
				}

				ball.collide(&(*iterator));
				iterator = bricks.erase(iterator);
			}
			if (iterator != bricks.end() && !collision){
				iterator++;
			}
		}
	}

	// Powerup collisions
	if (!powerups.empty()){
		for (Player &player : this->players){
			std::list<Powerup>::iterator iterator = this->powerups.begin();
			while (iterator != powerups.end()){

				// Check to see if the powerup hit the wall. If so, delete it
				if (iterator->hitWall()){
					iterator = powerups.erase(iterator);
					continue;
				}

				bool collision = false;

				if (Database::collide(&(*iterator), &player)){
					collision = true;
					iterator->collide(&player);
					iterator = powerups.erase(iterator);
				}
				if (iterator != powerups.end() && !collision){
					iterator++;
				}
			}
		}
	}
}

// You can easily configure which button does which movement by adding cases to input.h
// and then adding that button to 'player.movementKeys[MOVE_UP]' or whatever direction
// you want. 
//
// I imagine this could be done a little more efficiently using listeners instead of polling,
// however it's not terribly inefficient as it only ever iterates over 5 spots in the array.
void Database::processKeyPresses(){
	for (Player &player : players){
		Ball * ball = player.getBall();
		short * movementKeys = player.getMovementKeys();
		// This loop deals with game input (ie. moving player and lanching ball).
		//
		// keysPressed is an array that (eventually) contains every key on the keyboard
		// and possibly gamepad. When an element in keysPressed is true (ie. KEY_W, which
		// corresponds to 0 in the array), that key is being pressed. movementKeys (think
		// about renaming to actionKeys or something) is an array in each player that has
		// the various keys that player uses stored. They are set up like this:
		//
		// movementKeys[0] = MOVE_UP key
		// movementKeys[1] = MOVE_DOWN key
		// movementKeys[2] = MOVE_LEFT key
		// movementKeys[3] = MOVE_RIGHT key
		// movementKeys[4] = LAUNCH_BALL key
		//
		// So for each key on they keyboard / gamepad, if the player has that key set as 
		// an action key and is currently pressing that key, it does that action.
		for (int i = 0; i < KEYS_NUMBER; i++){
			if (Input::keysPressed[movementKeys[i]]){
				switch (i){
				case MOVE_UP:
					player.setdY(player.getCurrentSpeed());

					break;
				case MOVE_DOWN:
					player.setdY(-player.getCurrentSpeed());
					break;
				case MOVE_LEFT:
					if (Input::debug){
						fprintf(stderr, "Player 1 Y: %f\nPlayer 2 Y: %f\n\n", players[0].getY(), players[1].getY());
						fprintf(stderr, "Player 1 Score: %d\nPlayer 2 Score: %d\n\n", players[0].getScore(), players[1].getScore());
					}
					break;
				case MOVE_RIGHT:
					// In pong-out, you can only move up and down!
					break;
				case LAUNCH_BALL:
					if (ball){
						ball = player.popBall();
						ball->setAttached(false);
						if (player.getId() == 2){
							ball->setdX(-BALL_START_DX);
						}
						else{
							ball->setdX(BALL_START_DX);
						}
						ball->setdY(BALL_START_DY);
					}
					Input::keysPressed[movementKeys[i]] = false;
					break;
				}
			}
		}
		player.move();
		player.checkPowerups();

		// Other input (ex. escape, debug)
		/* Need to move the window pointer into the DB.
		if (Input::keysPressed[KEY_ESC]){
			glfwSetWindowShouldClose(GLTools::window, GL_TRUE);
		}
		*/
	}
}

void Database::moveBalls(){
	for (Ball &ball : this->balls){
		ball.move();
	}
}

void Database::cpuMove(){
	bool * cpuPressed;
	if (currentLoop == 0){
		cpuPressed = players[1].cpuMove(this->balls);

		// Set the correct keys in keysPressed
		for (int i = 0; i < 5; i++){
			Input::keysPressed[i + NUM_KEYBOARD_KEYS] = cpuPressed[i];
		}
	}

	// An attempt to make the CPU less jittery
	currentLoop = (currentLoop + 1) % CPU_WAIT;
}

void Database::generatePowerup(float x, float y, int direction){
	// generate a random powerup and add it to the list
	int powerup = rand() % 4 + 1;
	GLuint textureSampler;
	switch (powerup){
	case SPEED_UP:
		textureSampler = speedUpSampler;
		break;
	case SLOW_DOWN:
		textureSampler = slowDownSampler;
		break;
	case MULTI_BALL:
		textureSampler = multiBallSampler;
		break;
	case BIGGER_PADDLE:
		textureSampler = bigPaddleSampler;
		break;
	}


	powerups.push_back(Powerup(x, y, direction, powerup, textureSampler));
}


void Database::movePowerups(){
	for (Powerup &powerup : this->powerups){
		powerup.move();
	}
}