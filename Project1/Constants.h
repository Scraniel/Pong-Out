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

#define NUM_KEYBOARD_KEYS 11
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
#define KEY_ENTER 10
//CPU 'buttons' (put at the end of the keyboard buttons)
#define CPU_UP 11
#define CPU_DOWN 12
#define CPU_LEFT 13
#define CPU_RIGHT 14
#define CPU_LAUNCH 15

#define CPU_WAIT 1

#define ONE_PLAYER 0
#define TWO_PLAYER 1
#define SETTINGS 2
#define EXIT 3

const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);

extern short W_HEIGHT_NO_BORDER;
extern short W_WIDTH_NO_BORDER;


#endif