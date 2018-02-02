/*



*/
#pragma once
#include <string>

#include "../IGameObject.h"


namespace Rendering
{
	namespace Textures
	{
		class Texture : public IGameObject
		{
		public:
			Texture()  = default;
			~Texture() = default;

			GLuint LoadTexture(const std::string& filename, const int& width, const int& height);

		private:

		};
	}
}