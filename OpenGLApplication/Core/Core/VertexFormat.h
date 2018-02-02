/*



*/
#pragma once
#include "Dependencies\GLM\glm.hpp"

namespace Renderering
{
	struct VertexFormat
	{
		glm::vec3 position;
		glm::vec4 colour;

		VertexFormat(const glm::vec3 &position, const glm::vec4 &colour)
		{
			this->position = position;
			this->colour = colour;
		}
	};
}