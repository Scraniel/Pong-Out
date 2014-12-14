#include "GLTools.h"

GLuint GLTools::vertexBuffer, GLTools::colourBuffer, GLTools::programID, GLTools::vertexArrayID;
GLfloat GLTools::vertexData []= {
	0.0f, 0.0f, 0.0f,
	2.0f, 0.0f, 0.0f,
	0.0f, -2.0f, 0.0f,
	0.0f, -2.0f, 0.0f,
	2.0f, 0.0f, 0.0f,
	2.0f, -2.0f, 0.0f
};
GLFWwindow * GLTools::window;

/*
 * Public functions  
 */

void GLTools::GLInit(){
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	//TODO: Move to GLTools
	generateVAOs();
	setupVAOs();
}

void GLTools::renderRectangle(Rectangle * object){
	bindVAOs(object);
	reloadMVPUniform(object);
	// Draw the triangles!
	glDrawArrays(GL_TRIANGLES, 0, 2 * 3); // 2*(3 indices starting at 0) -> 2 triangles = square
}

void GLTools::enableVAO(){
	glBindVertexArray(vertexArrayID);
	// Use our shader
	glUseProgram(programID);
}

void GLTools::VAOcleanup(){
	// Cleanup VAO's and buffers
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &colourBuffer);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);
}

int GLTools::GLFWInit(GLFWkeyfun key_callback){
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

	return 0;
}

/*
 * Private / helper functions
 */

// This function may need to change if something is required to be rendered as something different than a rectangle
void GLTools::bindVAOs(Rectangle *object){
	// Buffer for Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, &vertexData[0], GL_STATIC_DRAW);

	// Buffer for Colours
	glm::vec3 colour[] = { object->getColour(), object->getColour(), object->getColour(), object->getColour(), object->getColour(), object->getColour() };
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, colour, GL_STATIC_DRAW);
}

void GLTools::reloadMVPUniform(Rectangle *object){
	// Get a handle for our "MVP" uniform.
	// Only at initialisation time.
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	glUseProgram(programID);
	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(object->getModel()[0][0]));
}

/*
* Creates VAO's
*/
void GLTools::generateVAOs(){

	// Creating and binding Vertex Array Object (VAO)
	glGenVertexArrays(1, &vertexArrayID);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colourBuffer);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("vertexShader.glsl", "fragmentShader.glsl");
}

void GLTools::setupVAOs(){
	glBindVertexArray(vertexArrayID);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
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