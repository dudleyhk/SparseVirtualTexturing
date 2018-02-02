/*



*/
#pragma once
#include <map>
#include <memory>

#include "..\Rendering\IGameObject.h"
#include "..\Rendering\Models\Triangle.h"
#include "..\Rendering\Models\Quad.h"

#include "ShaderManager.h"

namespace Managers
{
	class ModelsManager
	{
	public:
		ModelsManager();
		~ModelsManager();

		void Draw();
		void Update();
		void DeleteModel(const std::string& gameModelName);
		const Rendering::IGameObject& GetModel(const std::string& gameModelName) const;

	private:
		std::map<std::string, std::unique_ptr<Rendering::IGameObject>> gameModels;
	};
}