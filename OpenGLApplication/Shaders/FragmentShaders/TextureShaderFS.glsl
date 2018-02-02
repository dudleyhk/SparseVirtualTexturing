#version 430 core
layout(location = 0) out vec4 out_colour;

in vec4 colour;
in vec2 texCoord;

uniform sampler2D in_texture;


void main()
{
	out_colour = texture(in_texture, texCoord);
}