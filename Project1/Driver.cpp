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
#include <stdio.h>
#include <stdlib.h>
#include <list>
class Ball;

GLFWwindow* window;
GLuint VertexArrayID;
GLuint programID;
GLuint vertexbuffer;
GLuint colourBuffer;
short W_HEIGHT_NO_BORDER, W_WIDTH_NO_BORDER;

// These will eventually be moved to the Database class
Player players[] = { Player(100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, 100.0f, BLUE, KEY_W, KEY_S, KEY_A, KEY_D, SPACEBAR, 1, NULL), Player(W_WIDTH - 100.0f, (W_HEIGHT / 2.0) + 50, 25.0f, 100.0f, RED, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, R_CTRL, 2, NULL) };
// Consider making a vector
Ball balls[] = { Ball(players[0].getX() + players[0].getWidth(), players[0].getY() - (players[0].getHeight() / 2.0) + 12.5, 25.0f, 25.0f, players[0].getColour(), &players[0]), Ball(players[1].getX() - players[1].getWidth(), players[1].getY() - (players[1].getHeight() / 2.0) + 12.5, 25.0f, 25.0f, players[1].getColour(), &players[1]) };
// Making a linked list so arbitrary element deletion is efficient
std::list<Brick> bricks;


// Working on -1 -> 1 with x and y
GLfloat vertexData[] = {
	0.0f, 0.0f, 0.0f,
	2.0f, 0.0f, 0.0f,
	0.0f, -2.0f, 0.0f,
	0.0f, -2.0f, 0.0f,
	2.0f, 0.0f, 0.0f,
	2.0f, -2.0f, 0.0f
};

/*
* Creates VAO's
*/
static void generateVAOs(){

	// Creating and binding Vertex Array Object (VAO)
	glGenVertexArrays(1, &VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &colourBuffer);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
}

static void setupVAOs(){
	glBindVertexArray(VertexArrayID);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glEnableVertexAttribArray(1); // match layout # in shader

	// 2nd attribute buffer : colour NOT WORKING YET
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glVertexAttribPointer(
		1,		// attribute layout # above
		3,		// # of components (ie XYZ )
		GL_FLOAT,	// type of components
		GL_FALSE,	// need to be normalized?
		0,		// stride
		(void*)0	// array buffer offset
		);

	glBindVertexArray(0);
}

// This function may need to change if something is required to be rendered as something different than a rectangle
static void bindVAOs(Rectangle *object){
	// Buffer for Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &vertexData[0], GL_STATIC_DRAW);

	// Buffer for Colours
	glm::vec3 colour[] = { object->getColour(), object->getColour(), object->getColour(), object->getColour(), object->getColour(), object->getColour() };
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, colour, GL_STATIC_DRAW);
}

static void VAOcleanup(){
	// Cleanup VAO's and buffers
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colourBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);
}

static void reloadMVPUniform(Rectangle *object){
	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUseProgram(programID);
	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(object->getModel()[0][0]));
}

// You can easily configure which button does which movement by adding cases to input.h
// and then adding that button to 'player.movementKeys[MOVE_UP]' or whatever direction
// you want. 
static void processKeyPresses(){
	for (Player &player : players){
		Ball * ball = player.getBall();
		short * movementKeys = player.getMovementKeys();
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

void renderRectangle(Rectangle * object){
	bindVAOs(object);
	reloadMVPUniform(object);
	// Draw the triangles!
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*(3 indices starting at 0) -> 2 triangles = square
}

int main(void)
{

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Set up window hints
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Open a window
	window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Danny is cool", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	// Create our window's OpenGL context
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	// GLEW requires this for OpenGL >= 3.3
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW, Error Code:\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
	glfwSetKeyCallback(window, key_callback);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	generateVAOs();
	setupVAOs();

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


		glBindVertexArray(VertexArrayID);
		// Use our shader
		glUseProgram(programID);
		
		// render the players
		for (Player &player : players){
			if (debug){
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			renderRectangle(&player);
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

			renderRectangle(&ball);
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
					renderRectangle(&(*iterator));
				}
			}
			/*************************************************************************/
			if (iterator != bricks.end() && !collision){
				iterator++;
			}
		}
		
		// Swap buffers
		glfwSwapBuffers(window);

	} // Check if the ESC key was pressed or the window was closed
	while (!glfwWindowShouldClose(window));

	VAOcleanup();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
