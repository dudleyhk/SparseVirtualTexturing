/*



*/
#pragma once
#include "OpenGLApplication\Dependencies\GL\glew.h"
#include "OpenGLApplication\Dependencies\GL\freeglut.h"


namespace Core
{
	// Keep info about OpenGL Display Mode.
	struct FrameBufferInfo
	{
		unsigned int flags;
		bool msaa;

		FrameBufferInfo()
		{
			flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			msaa = false;
		}

		FrameBufferInfo(bool colour, bool depth, bool stencil, bool msaa)
		{
			flags = GLUT_DOUBLE;

			if(colour)  flags |= GLUT_RGBA | GLUT_ALPHA;
			if(depth)   flags |= GLUT_DEPTH;
			if(stencil) flags |= GLUT_STENCIL;
			if(msaa)    flags |= GLUT_MULTISAMPLE;

			this->msaa = msaa;
		}

		//TODO: implement copy constructor and assignment operator
	};
}
