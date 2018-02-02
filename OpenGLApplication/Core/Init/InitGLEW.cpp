/*



*/
#include "InitGLEW.h"


using namespace Core::Init;


void InitGLEW::Init()
{
	glewExperimental = true;
	if(glewInit() == GLEW_OK)
	{
		std::cout << "GLEW Initialised" << std::endl;
	}

	if(glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << "Glew version - " << glGetString(GL_VERSION) << std::endl;
	}
	else
	{
		std::cout << "ERROR: Glew 4.3 not supported" << std::endl;
	}
}
