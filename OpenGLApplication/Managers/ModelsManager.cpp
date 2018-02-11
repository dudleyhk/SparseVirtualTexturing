/*



*/
#include <fstream>
#include <sstream>

#include "..\Core\Core\ContainerUtilities.h"
#include "..\Rendering\Texture\Texture.h"

#include "ModelsManager.h"

using namespace Managers;
using namespace Rendering;



ModelsManager::ModelsManager()
{
	//Models::Triangle* triangle = new Models::Triangle();
	//triangle->SetProgram(ShaderManager::GetShader("TextureShader"));
	//triangle->Create();
	//gameModels["Triangle"].reset(triangle);
	// 
	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("TextureShader"));
	quad->Create();
	gameModels["Quad"].reset(quad);


	//Models::Terrain* terrain = new Models::Terrain();
	//terrain->SetProgram(ShaderManager::GetShader("TextureShader"));
	//terrain->Create();
	//gameModels["Terrain"].reset(terrain);
}



ModelsManager::~ModelsManager()
{
	gameModels.clear();
}



void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	if(!Algorithms::Map::contains(gameModels, gameModelName))
	{
		std::cout << "ERROR: Attempting to get invalid gamemodel " << gameModelName << std::endl;
		return;
	}

	IGameObject* model = gameModels[gameModelName].release();
	model->Destroy();
	gameModels.erase(gameModelName);
}



const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	if(!Algorithms::Map::contains(gameModels, gameModelName))
	{
		std::cout << "ERROR: Attempting to get invalid gamemodel " << gameModelName << std::endl;
	}
	return *gameModels.at(gameModelName).get();
}



void ModelsManager::Update()
{
	for(const auto& model : gameModels)
	{
		model.second->Update();
	}
}



void ModelsManager::Draw()
{
	for(const auto& model : gameModels)
	{
		model.second->Draw();
	}
}




/* Code to open and load a model file.
TODO: Put this into it own class.

// https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ*/

void ModelsManager::LoadObject(const char* filename, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements)
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
		else if(line.substr(0, 2) == "f ")
		{
			std::string str;
			std::istringstream s(line.substr(2));
			std::vector<std::string> line;

			int count = 1;
			GLushort a, b, c;
			auto end = std::string("");
			while(line.size() < 3)
			{
				s >> end;
				std::string vertex_data;
				for(auto character : end)
				{
					if(character == '/') break;
					vertex_data += character;
				}

				if(count == 1)
				{
					std::stringstream(vertex_data) >> a;
					a--;
					elements.push_back(a);
				}

				if(count == 2)
				{
					std::stringstream(vertex_data) >> b;
					b--;
					elements.push_back(b);
				}

				if(count == 3)
				{
					std::stringstream(vertex_data) >> c;
					c--;
					elements.push_back(c);
				}
				line.push_back(end);
				count++;
			}
		}
		else if(line[0] == '#')
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
