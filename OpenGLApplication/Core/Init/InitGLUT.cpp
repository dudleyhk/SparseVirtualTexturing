/*



*/
#include "InitGLUT.h"

using namespace Core::Init;



Core::IListener* InitGLUT::listener;
Core::WindowInfo InitGLUT::window_information;


void InitGLUT::Init(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo, const Core::FrameBufferInfo& framebufferInfo)
{
	int fake_argc = 1;
	char* fake_argv[] = {"fake", nullptr };
	glutInit(&fake_argc, fake_argv);

	window_information = windowInfo;

	if(contextInfo.core)
	{
		glutInitContextVersion(contextInfo.major_version, contextInfo.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebufferInfo.flags);
	glutInitWindowPosition(windowInfo.position_x,
						   windowInfo.position_y);
	glutInitWindowSize(windowInfo.width, windowInfo.height);

	glutCreateWindow(windowInfo.name.c_str());

	

	std::cout << "GLUT Initialised" << std::endl;

	// Rendering Callbacks
	glutIdleFunc(IdleCallback);
	glutCloseFunc(CloseCallback);
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ResizeCallback);

	Init::InitGLEW::Init();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	PrintOpenGLInfo(windowInfo, contextInfo);
}

void InitGLUT::Run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}


void InitGLUT::Close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void InitGLUT::EnterFullscreen()
{
	glutFullScreen();
}

void InitGLUT::ExitFullscreen()
{
	glutLeaveFullScreen();
}

void InitGLUT::PrintOpenGLInfo(const Core::WindowInfo& windowInfo, const Core::ContextInfo& contextInfo)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor   = glGetString(GL_VENDOR);
	const unsigned char* version  = glGetString(GL_VERSION);

	std::cout << "*******************************************************************************" << std::endl;

	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
	std::cout << "GLUT:\tInitial window is '" << windowInfo.name << "', with dimensions (" << windowInfo.width
		<< " X " << windowInfo.height;
	std::cout << ") starts at (" << windowInfo.position_x << " X " << windowInfo.position_y;
	std::cout << ") and " << ((windowInfo.is_resizable) ? "is" : "is not ") << " redimensionable" << std::endl;
	std::cout << "GLUT:\tInitial Framebuffer contains double buffers for" << std::endl;

	std::cout << "GLUT:\t OpenGL context is " << contextInfo.major_version << "." << contextInfo.minor_version;
	std::cout << " and profile is " << ((contextInfo.core) ? "core" : "compatibility") << std::endl;

	std::cout << "*****************************************************************" << std::endl;
}

void InitGLUT::SetListener(Core::IListener* iListener)
{
	listener = iListener;
}

// Called when events are not being received
void InitGLUT::IdleCallback()
{
	glutPostRedisplay();
}

void InitGLUT::DisplayCallback()
{
	if(listener)
	{
		listener->NotifyBeginFrame();
		listener->NotifyDisplayFrame();

		glutSwapBuffers();

		listener->NotifyEndFrame();
	}
}

void InitGLUT::ResizeCallback(int width, int height)
{
	if(window_information.is_resizable)
	{
		if(listener)
			listener->NotifyResize(width, height, window_information.width, window_information.height);
	
		window_information.width = width;
		window_information.height = height;
	}
}

void InitGLUT::CloseCallback()
{
	Close();
}
