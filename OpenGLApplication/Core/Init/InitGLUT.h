/*



*/
#pragma once
#include <iostream>
#include <memory>

#include "..\Core\IListener.h"
#include "ContextInfo.h"
#include "FrameBufferInfo.h"
#include "WindowInfo.h"
#include "InitGLEW.h"



namespace Core
{
	namespace Init
	{
		class InitGLUT
		{

		public:             
			static void Init(const Core::WindowInfo& window,
							 const Core::ContextInfo& context,
							 const Core::FrameBufferInfo& framebufferInfo);

			static void Run();
			static void Close();

			void EnterFullscreen();
			void ExitFullscreen();

			static void PrintOpenGLInfo(const Core::WindowInfo& windowInfo,
										const Core::ContextInfo& context);
			
			static void SetListener(Core::IListener* iListener);
		
		private:
			static void IdleCallback();
			static void DisplayCallback();
			static void ResizeCallback(int width, int height);
			static void CloseCallback();
		
			static Core::IListener* listener;
			static Core::WindowInfo window_information;
		
		};
	}
}
