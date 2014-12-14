/*
*TODO: 
*   1. Make a 'in game object' parent class to use for bricks, powerups, etc.
*      It will contain information about sprites, state, etc.
*   2. Create a fileformat to allow for easily imputted levels
*/
#include "Input.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Database.h"
#include "GLTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <list>
class Ball;

// These will eventually be moved to the Database class
Player players[] = { Player(100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, 100.0f, BLUE, KEY_W, KEY_S, KEY_A, KEY_D, SPACEBAR, 1, NULL), Player(W_WIDTH - 100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, 100.0f, RED, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, R_CTRL, 2, NULL) };
// Consider making a vector
Ball balls[] = { Ball(players[0].getX() + players[0].getWidth(), players[0].getY() - (players[0].getHeight() / 2.0) + 12.5, 25.0f, 25.0f, players[0].getColour(), &players[0]), Ball(players[1].getX() - players[1].getWidth(), players[1].getY() - (players[1].getHeight() / 2.0) + 12.5, 25.0f, 25.0f, players[1].getColour(), &players[1]) };
// Making a linked list so arbitrary element deletion is efficient
std::list<Brick> bricks;

// You can easily configure which button does which movement by adding cases to input.h
// and then adding that button to 'player.movementKeys[MOVE_UP]' or whatever direction
// you want. 
//
// I imagine this could be done a little more efficiently using listeners insetad of polling.
static void processKeyPresses(){
	for (Player &player : players){
		Ball * ball = player.getBall();
		short * movementKeys = player.getMovementKeys();
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
			if (keysPressed[movementKeys[i]]){
				switch (i){
				case MOVE_UP:
					player.setdY(15);
					
					break;
				case MOVE_DOWN:
					player.setdY(-15);
					break;
				case MOVE_LEFT:
					if (debug){
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
					keysPressed[movementKeys[i]] = false;
					break;
				}
			}
		}
		player.move();
	}
}

int main(void)
{

	if (GLTools::GLFWInit(key_callback) < 0){
		return -1;
	}

	GLTools::GLInit();

	// Set balls to be attached to players
	players[0].setBall(&balls[0]);
	players[1].setBall(&balls[1]);

	/*
	 * This should be moved into the input class so that levels can be specified
	 * via a level file
	 */
	// Create bricks
	for (int i = 0; i < 14; i++){
		bricks.push_back(Brick( (2*W_WIDTH) / 5.0, W_HEIGHT - i*BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, GREEN, false, 1));
	}
	
	for (int i = 0; i < 14; i++){
		bricks.push_back(Brick( (3*W_WIDTH) / 5.0, W_HEIGHT - i*BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT, GREEN, false, 1));
	}


	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Check if any events (eg. key presses) have happened
		glfwPollEvents();

		processKeyPresses();

		GLTools::enableVAO();
		
		// render the players
		for (Player &player : players){
			if (debug){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			GLTools::renderRectangle(&player);
		}

		// render the balls
		for (Ball &ball : balls){

			ball.move();
			
			/*TODO: MOVE THIS INTO DATABASE ONCE YOU MOVE ALL THE OBJECTS INTO THERE!*/
			for (Player &player : players){
				if (Database::collide(&ball, &player) && !ball.isAttached()){
					ball.collide(&player);
				}
			}
			/*************************************************************************/

			GLTools::renderRectangle(&ball);
		}
		// render the bricks
		// Have to use this weird iterator while loop because of how the list class works
		// (eg. list.erase returns the next element, so we need a guard at the end to see
		// if the iterator has overstepped the bounds of the bricks list)
		std::list<Brick>::iterator iterator = bricks.begin();
		while (iterator != bricks.end()){
			bool collision = false;

			/*TODO: MOVE THIS INTO DATABASE ONCE YOU MOVE ALL THE OBJECTS INTO THERE!*/
			for (Ball &ball : balls){
				if (Database::collide(&ball, &(*iterator)) && !ball.isAttached()){
					collision = true;
					ball.collide(&(*iterator));
					iterator = bricks.erase(iterator);
					break;
				}
				else{
					GLTools::renderRectangle(&(*iterator));
				}
			}
			/*************************************************************************/
			if (iterator != bricks.end() && !collision){
				iterator++;
			}
		}
		
		// Swap buffers
		glfwSwapBuffers(GLTools::window);

	} // Check if the ESC key was pressed or the window was closed
	while (!glfwWindowShouldClose(GLTools::window));

	GLTools::VAOcleanup();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}