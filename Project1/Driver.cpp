/*
*TODO: Make a 'in game object' parent class to use for player, ball, bricks, powerups, etc. It may end up replacing the rectangle class.
*      It will contain information about sprites, state, etc. 
*/
#include "Input.h"
#include "Player.h"
#include "Ball.h"
#include "Database.h"
#include <stdio.h>
#include <stdlib.h>
class Ball;

GLFWwindow* window;
GLuint VertexArrayID;
GLuint programID;
GLuint vertexbuffer;
GLuint colourBuffer;
short W_HEIGHT_NO_BORDER, W_WIDTH_NO_BORDER;
Player players[] = { Player(-300.0f, 0.0f, 25.0f, 100.0f, KEY_W, KEY_S, KEY_A, KEY_D, NULL), Player(300.0f, 0.0f, 25.0f, 100.0f, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, NULL) };
Ball balls[] = { Ball(-300.0f, 0.0f, 25.0f, 25.0f, &players[0]), Ball(300.0f, 0.0f, 25.0f, 25.0f, &players[1]) };

// Working on -1 -> 1 with x and y
GLfloat vertexData[] = {
	-1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 0.0f
};

/*
* Creates VAO's
*/
static void generateVAOs(){

	// Creating and binding Vertex Array Object (VAO)
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
}

static void setupVAOs(){
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
}

// This function may need to change if something is required to be rendered as something different than a rectangle
static void bindVAOs(){

	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
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

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &object->getModel()[0][0]);
}

// You can easily configure which button does which movement by adding cases to input.h
// and then adding that button to 'player.movementKeys[MOVE_UP]' or whatever direction
// you want. 
static void processKeyPresses(){
	for (Player &player : players){
		short * movementKeys = player.getMovementKeys();
		for (int i = 0; i < MOVE_KEYS_NUMBER; i++){
			if (keysPressed[movementKeys[i]]){
				switch (i){
				case MOVE_UP:
					player.setdY(10);
					if (debug){
						fprintf(stderr, "Player 1 Y: %f\nPlayer 2 Y: %f\n\n", players[0].getY(), players[1].getY());
					}
					break;
				case MOVE_DOWN:
					player.setdY(-10);
					if (debug){
						fprintf(stderr, "Player 1 Y: %f\nPlayer 2 Y: %f\n\n", players[0].getY(), players[1].getY());
					}
					break;
				case MOVE_LEFT:
					// In pong-out, you can only move up and down!
					break;
				case MOVE_RIGHT:
					// In pong-out, you can only move up and down!
					break;
				}
			}
		}

		player.move();
	}
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
	window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Modern OpenGL", NULL, NULL);

	// TODO: Find a way to do this without using magic numbers. 
	W_HEIGHT_NO_BORDER = W_HEIGHT - 25;
	W_WIDTH_NO_BORDER = W_WIDTH - 25;

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

	generateVAOs();
	bindVAOs();


	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Check if any events (eg. key presses) have happened
		glfwPollEvents();

		processKeyPresses();

		// Use our shader
		glUseProgram(programID);

		// render the players
		for (Player &player : players){
			reloadMVPUniform(&player);

			// Not actually using VAO's right now. FIX THIS.
			setupVAOs();

			// Draw the triangles!
			glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*(3 indices starting at 0) -> 2 triangles = square

			glDisableVertexAttribArray(0);
		}

		// render the balls
		for (Ball &ball : balls){
			/*TODO: MOVE THIS INTO DATABASE ONCE YOU MOVE ALL THE OBJECTS INTO THERE!*/
			for (Player &player : players){
				Database::collide(&ball, &player);
			}

			/*************************************************************************/
			ball.move();

			reloadMVPUniform(&ball);

			// Not actually using VAO's right now. FIX THIS.
			setupVAOs();

			// Draw the triangles!
			glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*(3 indices starting at 0) -> 2 triangles = square

			glDisableVertexAttribArray(0);
		}
		
		// Swap buffers
		glfwSwapBuffers(window);

	} // Check if the ESC key was pressed or the window was closed
	while (!glfwWindowShouldClose(window));
	fprintf(stderr, "%d\n%d\n", players[0].getY(), players[1].getY());
	VAOcleanup();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
