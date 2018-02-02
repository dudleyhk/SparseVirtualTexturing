/*



*/
#pragma once
#include <string>
#include <map>

#include "..\Dependencies\GL\glew.h"
#include "..\Dependencies\GL\freeglut.h"


namespace Managers
{
	class ShaderManager
	{
	public:
		ShaderManager() = default;
		~ShaderManager();

		/* Create a vertex and fragment shader using default .glsl extension */
		void CreateProgram(const std::string& shaderName, 
						   const std::string& vertexShaderPath,
						   const std::string& vertexShaderFilename,
						   const std::string& fragmentShaderPath, 
						   const std::string& fragmentShaderFilename,
						   const std::string& extension = ".glsl");

		static const GLuint GetShader(const std::string& shaderName);
		// TODO: DeleteShader function

	private:
		std::string ReadShader(const std::string& filename);
		const GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName);
	
		static std::map<std::string, GLuint> programs;
	
	};
}