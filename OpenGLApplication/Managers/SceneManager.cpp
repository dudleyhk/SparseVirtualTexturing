/*
	


*/
#include <fstream>

#include "SceneManager.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/STB/stb_image.h"



using namespace Managers;


SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = std::make_unique<ShaderManager>();
	if(!shader_manager)
	{
		std::cout << "ERROR instantiating ShaderManager class" << std::endl;
		return;
	}

	// TODO: Run this directly through the shader manager
	shader_manager->CreateProgram("ColourShader",
								  "Shaders\\VertexShaders\\",   "VertexShader",
								  "Shaders\\FragmentShaders\\", "FragmentShader");

	shader_manager->CreateProgram("TextureShader",
								  "Shaders\\VertexShaders\\",   "TextureShaderVS",
								  "Shaders\\FragmentShaders\\", "TextureShaderFS");



	models_manager = std::make_unique<ModelsManager>();
	if(!models_manager)
	{
		std::cout << "ERROR instantiating ModelManager class" << std::endl;
		return;
	}

	// TODO: Create a texture loading class (this could be something todo with ModelManager).
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;

	//TODO: Error check data
	unsigned char *data = stbi_load("..//Resources//DestertMountainTexture.jpg", &width, &height, &nrChannels, 0);

	//stbi_info


	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// TODO: Output image loaded details in TextureManager




	// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices, temp_normals;
	std::vector<glm::vec2> temp_normals;

	FILE* file = fopen("..//Resources//Model.obj", "r");
	if(file == nullptr)
	{
		std::cout << "Impossible to open the file ! \n" << std::endl;
		return;
	}


}


void SceneManager::NotifyBeginFrame()
{
	models_manager->Update();

	// TODO: Create an interface class to handle the Parsing and Generation
	// GenerationTool::Core::Init init;
	// init.ReadWriteExample();
}

void SceneManager::NotifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	
	


















	//glBindTexture(GL_TEXTURE_2D, texture);
	models_manager->Draw();
}

void SceneManager::NotifyEndFrame()
{
	//nothing here for the moment
}

void SceneManager::NotifyResize(int width, int height,
								  int previous_width, int previous_height)
{
	//nothing here for the moment 
}