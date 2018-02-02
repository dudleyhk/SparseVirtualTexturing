/*



*/
#pragma once
#include <iostream>

#include "OpenGLApplication\Dependencies\GL\glew.h"
#include "OpenGLApplication\Dependencies\GL\freeglut.h"



namespace Core
{
	namespace Init
	{
		class InitGLEW
		{
		public:
			InitGLEW() = default;
			~InitGLEW() = default;

			static void Init();

		private:

		};
	}
}