#ifndef STDGLINCLUDES_H
#define STDGLINCLUDES_H

#include <GL/glew.h>

// Using the dynamic version of gflw instead of static
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

#endif