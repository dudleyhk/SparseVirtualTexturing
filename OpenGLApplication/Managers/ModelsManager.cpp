/*



*/
#include "..\Core\Core\ContainerUtilities.h"
#include "..\Rendering\Texture\Texture.h"

#include "ModelsManager.h"

using namespace Managers;
using namespace Rendering;



ModelsManager::ModelsManager()
{
	//Models::Triangle* triangle = new Models::Triangle();
	//triangle->SetProgram(ShaderManager::GetShader("ColourShader"));
	//triangle->Create();
	//gameModels["Triangle"].reset(triangle);

	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("TextureShader"));
	quad->Create();
	gameModels["Quad"].reset(quad);


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