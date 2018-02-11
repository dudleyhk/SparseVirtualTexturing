/*



*/
#pragma once
#include "Model.h"





namespace Rendering
{
	namespace Models
	{
		class Terrain : public Models::Model
		{
		public:
			Terrain() = default;
			~Terrain() = default;
			// TODO: Work in this clean up stuff. 
			/*if (vbo_vertices != 0)
      glDeleteBuffers(1, &vbo_vertices);
    if (vbo_normals != 0)
      glDeleteBuffers(1, &vbo_normals);
    if (ibo_elements != 0)
      glDeleteBuffers(1, &ibo_elements);
*/

			void Create();
			virtual void Draw() override final;
			virtual void Update() override final;

			const glm::vec3 CalculateNormal(GLuint x, GLuint z);
			float GetHeight(const GLuint width, const GLuint depth);

		private:



			// TODO: Create a terraindata strcut
			std::vector<float> height;
			const GLuint width = 5;//251;
			const GLuint depth = 5;//251;
			float step = 0.5f;

			// MESH
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<GLuint> indices;
		};
	}
}