#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <glm/glm.hpp>

#define W_HEIGHT 540
#define W_WIDTH 960
#define MOVE_KEYS_NUMBER 4
#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3
#define KEY_W 0
#define KEY_A 1
#define KEY_S 2
#define KEY_D 3
#define KEY_UP 4
#define KEY_LEFT 5
#define KEY_DOWN 6
#define KEY_RIGHT 7
const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);

extern short W_HEIGHT_NO_BORDER;
extern short W_WIDTH_NO_BORDER;
extern bool debug;


#endif