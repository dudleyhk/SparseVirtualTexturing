/*



*/
#include <iostream>
#include <fstream>
#include <vector>

#include "..\Core\Core\ContainerUtilities.h"

#include "ShaderManager.h"


using namespace Managers;



std::map<std::string, GLuint> ShaderManager::programs;



ShaderManager::~ShaderManager()
{
	// This works when placed in the create program function
	for(auto iter = programs.begin(); iter != programs.end(); iter++)
	{
		GLuint pr = iter->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}



void ShaderManager::CreateProgram(const std::string& shaderName, 
								  const std::string& vertexShaderPath,
								  const std::string& vertexShaderFilename,
								  const std::string& fragmentShaderPath, 
								  const std::string& fragmentShaderFilename,
								  const std::string& extension)
{
	// read the shader files and save the code. 
	std::string vertex_shader_code   = ReadShader(vertexShaderPath + vertexShaderFilename + extension);
	std::string fragment_shader_code = ReadShader(fragmentShaderPath + fragmentShaderFilename + extension);

	GLuint vertex_shader   = CreateShader(GL_VERTEX_SHADER,   vertex_shader_code,   vertexShaderFilename);
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, fragmentShaderFilename);

	// create the program handle, attach the shaders and link it.
	int link_result = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	// Check for link errors
	if(link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, nullptr, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return;
	}

	const auto& ret = programs.insert(std::pair<std::string, GLuint>(shaderName, program));
	if(!ret.second)
	{
		std::cout << "MESSAGE: Attempting to insert a shader " << shaderName << " which already exists in Programs. Setting it instead." << std::endl;
		programs[shaderName] = program;
	}



}


const GLuint ShaderManager::GetShader(const std::string& shaderName)
{
	if(!Algorithms::Map::contains(programs, shaderName))
	{
		std::cout << "ERROR: Attempting to get invalid shader " << shaderName << std::endl;
		return -1;
	}
	return programs[shaderName];
}


// Extract shaders content and create both shaders, and load them into the program which is returned to be used in rendering loop.
std::string ShaderManager::ReadShader(const std::string& filename)
{
	std::string shader_code;
	std::ifstream file(filename.c_str(), std::ios::in);

	if(!file.good())
	{
		std::cout << "ERROR: Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shader_code.resize(static_cast<unsigned int>(file.tellg()));
	file.seekg(0, std::ios::beg);
	file.read(&shader_code[0], shader_code.size());
	file.close();

	return shader_code;
}



// Create and compile a shader.
const GLuint ShaderManager::CreateShader(const GLenum shaderType, const std::string& source, const std::string& shaderName)
{
	auto compile_result = 0;

	GLint shader = glCreateShader(shaderType);
	const char* shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if(compile_result == GL_FALSE)
	{
		auto info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		std::cout << "ERROR Compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}
