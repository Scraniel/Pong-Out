#version 330 core
in vec3 interpolate_colour;
// Ouput data
out vec3 colour;

void main()
{

	// Output color = red 
	colour = interpolate_colour;

}