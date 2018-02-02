/*



*/
#pragma once
#include "..\Dependencies\GLM\glm.hpp"


struct VertexFormat
{
	glm::vec3 position;
	glm::vec4 colour;
	glm::vec2 uv;

	VertexFormat(const glm::vec3 &position, const glm::vec4 &colour, const glm::vec2& uv)
	{
		this->position = position;
		this->colour = colour;
		this->uv = uv;
	}
};