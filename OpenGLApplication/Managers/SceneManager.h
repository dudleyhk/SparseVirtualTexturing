/*



*/
#pragma once
#include <memory>



#include "..\Core\Core\IListener.h"

#include "ModelsManager.h"
#include "ShaderManager.h"



namespace Managers
{
	class SceneManager : public Core::IListener
	{
	public:
		SceneManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyResize(int width, int height,
								  int previousWidth, int previousHeight);

	private:
		GLuint texture;

		std::unique_ptr<Managers::ShaderManager> shader_manager = nullptr;
		std::unique_ptr<Managers::ModelsManager> models_manager = nullptr;
	};
}