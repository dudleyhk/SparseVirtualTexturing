#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_colour;
layout(location = 2) in vec2 in_texCoord;

out vec4 colour;
out vec2 texCoord;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	colour    = in_colour;
	texCoord  = in_texCoord;

	gl_Position = proj * view * trans * vec4(in_position, 1.f);

}