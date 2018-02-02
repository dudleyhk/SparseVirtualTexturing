/*



*/
#pragma once
#include "Core\Init\InitGLUT.h"
#include "Managers\SceneManager.h"

int main()
{
	Core::WindowInfo window(std::string("Texture Streaming Application"), 500, 500, 800, 600, true);
	Core::ContextInfo context(4, 3, true);
	Core::FrameBufferInfo frameBufferInfo(true, true, true, true);

	Core::Init::InitGLUT::Init(window, context, frameBufferInfo);
	
	std::unique_ptr<Core::IListener> scene = std::make_unique<Managers::SceneManager>();
	Core::Init::InitGLUT::SetListener(scene.get());
	
	
	
	Core::Init::InitGLUT::Run();

	return 0;
}

