/*
	


*/
#include <fstream>
#include <sstream>

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


	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;

	// This call somewhere more suitable. 
	LoadObject("..//Resources//Model.obj", vertices, normals, elements);





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



/* Code to open and load a model file. 
TODO: Put this into it own class.

// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ*/
	
void SceneManager::LoadObject(const char* filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements)
{	
	std::ifstream in(filename, std::ios::in);
	if(!in)
	{
		std::cout << "Cannot open file - " << filename << std::endl;
		return;
	}

	std::string line;
	while(getline(in, line))
	{
		if(line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			glm::vec4 v;
			s >> v.x >> v.y >> v.z;
			v.w = 1.0f;
			vertices.push_back(v);
			std::cout << "vert: (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::string str;
			std::istringstream s(line.substr(2));
		

			// TODO: run through each element and check the first value of 
			//			each block of numbers.
			// while(s != s.end())
			GLushort a, b, c;
			s >> a;
			s >> b;
			s >> c;
			a--; b--; c--;
			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		}
		else if (line[0] == '#')
		{
			// ignore this line.
		}
		else
		{
			// ignore this line.
		}
	}

	normals.resize(vertices.size(), glm::vec3(0.f, 0.f, 0.f));
	for(auto i = 0; i < elements.size(); i += 3)
	{
		auto ia = elements[i];
		auto ib = elements[i + 1];
		auto ic = elements[i + 2];

		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
			glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));

		normals[ia] = normal;
		normals[ib] = normal;
		normals[ic] = normal;
	}
}
