#version 430 core
layout(location = 0) out vec4 out_colour;
 
in vec4 colour;

void main()
{
  out_colour = colour;
}