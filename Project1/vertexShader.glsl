#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vert_colour;

uniform mat4 MVP;

out vec3 interpolate_colour;

void main(){

	vec4 v = vec4(vertexPosition_modelspace, 1.0);

    gl_Position = MVP * v;

	interpolate_colour = vert_colour;
}
