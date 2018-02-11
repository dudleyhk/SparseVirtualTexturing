/*
	


*/

#include "SceneManager.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/STB/stb_image.h"

#include "../Core/Init/InitGLUT.h"


using namespace Managers;


SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shader_manager = std::make_unique<ShaderManager>();
	if(!shader_manager)
	{
		std::cout << "ERROR instantiating ShaderManager class" << std::endl;
		return;
	}

	// TODO: Run this directly through the shader manager
	shader_manager->CreateProgram("ColourShader",
								  "Shaders\\VertexShaders\\",   "VertexShader",
								  "Shaders\\FragmentShaders\\", "FragmentShader");

	shader_manager->CreateProgram("TextureShader",
								  "Shaders\\VertexShaders\\",   "TextureShaderVS",
								  "Shaders\\FragmentShaders\\", "TextureShaderFS");



	models_manager = std::make_unique<ModelsManager>();
	if(!models_manager)
	{
		std::cout << "ERROR instantiating ModelManager class" << std::endl;
		return;
	}

	// TODO: Create a texture loading class (this could be something todo with ModelManager).
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrChannels;

	//TODO: Error check data
	unsigned char *data = stbi_load("..//Resources//DestertMountainTexture.jpg", &width, &height, &nrChannels, 0);

	//stbi_info


	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// TODO: Output image loaded details in TextureManager

	

	// TODO: Encapsulate this... This is the setup of a frame buffer object.
	// A frame buffer allows you to draw to a memory buffer instead of a screen buffer.
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	
	glGenRenderbuffers(1, &render_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_BGRA, Core::Init::InitGLUT::GetWidth(), Core::Init::InitGLUT::GetHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind
	
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, render_buffer);


	bool status = glCheckFramebufferStatus(fbo);
	if(!status)
	{
		std::cout << "ERROR: Initialising the Framebuffer" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind


	/* Init Pixel Buffer Object */
	GLint channel_count = 4;
	GLint data_size = Core::Init::InitGLUT::GetWidth() * Core::Init::InitGLUT::GetHeight() * channel_count;
	
	// Create two pixel buffer objects to speed up the streaming transfer performance
	// These two pbos are being used to pack data in from the FBO. 
	// glGenBuffersARB(4, pbo); // Add another two at the end to unpack from.
	glGenBuffersARB(2, pbo);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo[0]);
	glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, data_size, 0, GL_STREAM_DRAW_ARB);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo[1]);
	glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, data_size, 0, GL_STREAM_DRAW_ARB);
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
}

SceneManager::~SceneManager()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &render_buffer);
	
	glDeleteBuffers(2, pbo);
}


void SceneManager::NotifyBeginFrame()
{
	models_manager->Update();


	// TODO: Create an interface class to handle the Parsing and Generation
	// GenerationTool::Core::Init init;
	// init.ReadWriteExample();
}

void SceneManager::NotifyDisplayFrame()
{
	/* WRITE TO PIXEL BUFFER OBJECT */

	// "index" is used to read pixels from framebuffer to a PBO
	// "nextIndex" is used to update pixels in the other PBO
	static int index = 0;
	int nextIndex = 0;                  // pbo index used for next frame
	
	index = (index + 1) % 2;
	nextIndex = (index + 1) % 2;

	glReadBuffer(GL_BACK);

	auto window_width = glutGet(GLUT_WINDOW_WIDTH);
	auto window_height = glutGet(GLUT_WINDOW_HEIGHT);


	// copy pixels from framebuffer to PBO
	// Use offset instead of ponter.
	// OpenGL should perform asynch DMA transfer, so glReadPixels() will return immediately.
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo[index]);
	glReadPixels(0, 0, window_width, window_height, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	// map the PBO that contain framebuffer pixels before processing it
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo[nextIndex]);
	GLubyte* src = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
	if(src)
	{
		// proccessPixels(src, ...);
		glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB);
	}
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);





	/* RENDER TO THE FRAMEBUFFER */
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	models_manager->Draw();
	
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	





	/* RENDER TO SCREEN BUFFER. */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	
	//glBindTexture(GL_TEXTURE_2D, texture);
	models_manager->Draw();


}

void SceneManager::NotifyEndFrame()
{
	}

void SceneManager::NotifyResize(int width, int height,
								  int previous_width, int previous_height)
{
	//nothing here for the moment 
}


