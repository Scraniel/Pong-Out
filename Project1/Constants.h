#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <glm/glm.hpp>

#define W_HEIGHT 700
#define W_WIDTH 1520

#define BALL_START_DX 15
#define BALL_START_DY 8

#define BRICK_HEIGHT 50
#define BRICK_WIDTH 25

#define KEYS_NUMBER 5
#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3
#define LAUNCH_BALL 4

#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3
#define KEY_UP 4
#define KEY_LEFT 5
#define KEY_DOWN 6
#define KEY_RIGHT 7
#define SPACEBAR 8
#define R_CTRL 9

const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);

extern short W_HEIGHT_NO_BORDER;
extern short W_WIDTH_NO_BORDER;
extern bool debug;


#endif