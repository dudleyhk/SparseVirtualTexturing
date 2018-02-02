#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_colour;

out vec4 colour;

void main()
{
	gl_Position = vec4(in_position, 1.0);
	colour = in_colour;
}