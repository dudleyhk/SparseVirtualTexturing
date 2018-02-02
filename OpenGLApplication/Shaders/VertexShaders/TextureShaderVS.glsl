#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_colour;
layout(location = 2) in vec2 in_texCoord;

out vec4 colour;
out vec2 texCoord;



void main()
{
	gl_Position = vec4(in_position, 1.0);
	colour = in_colour;

	// Do this because most images y coords are inverted with openGL.
	texCoord    = in_texCoord; //vec2(in_texCoord.x, 1.0 - in_texCoord.y);
}