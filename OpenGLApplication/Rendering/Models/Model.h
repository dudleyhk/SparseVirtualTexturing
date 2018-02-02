/*



*/
#pragma once
#include <vector>

#include "..\IGameObject.h"

// TODO: Models use the same program (Shader) rather than each being assigned a new one. 
// TODO: Change map to vector. Maps are slow.

namespace Rendering
{
	namespace Models
	{
		class Model : public IGameObject
		{
		public: 
			Model() = default;
			virtual ~Model();			

			virtual void Draw()    override;
			virtual void Update()  override;
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

		protected:
			GLuint vao;
			GLuint ebo; // TODO: Work out if this needs to be in a vector as well.
			GLuint program;
			std::vector<GLuint> vbos;
		};
	}
}