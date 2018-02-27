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

	// TODO: This code isn't encapsulated at all.
	InitShaders();
	models_manager = std::make_unique<ModelsManager>();
	if(!models_manager)
	{
		std::cout << "ERROR instantiating ModelManager class" << std::endl;
		return;
	}

	InitTexture();
	// InitFramebuffer();
	InitPixelBuffer();



}

SceneManager::~SceneManager()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &render_buffer);
	
	// 2 = PBO_COUNT
	glDeleteBuffersARB(2, pbo);

	// TODO: Clean up. 
	delete[] colour_buffer;
	colour_buffer = nullptr;

	if(image_data)
	{
		delete[] image_data;
		image_data = nullptr;
	}
}

void SceneManager::InitShaders()
{
	shader_manager = std::make_unique<ShaderManager>();
	if(!shader_manager)
	{
		std::cout << "ERROR instantiating ShaderManager class" << std::endl;
		return;
	}

	// TODO: Run this directly through the shader manager
	shader_manager->CreateProgram("ColourShader",
								  "Shaders\\VertexShaders\\", "VertexShader",
								  "Shaders\\FragmentShaders\\", "FragmentShader");

	shader_manager->CreateProgram("TextureShader",
								  "Shaders\\VertexShaders\\", "TextureShaderVS",
								  "Shaders\\FragmentShaders\\", "TextureShaderFS");


}

void SceneManager::InitTexture()
{
	width     = image_width;
	height    = image_height;
	channel   = nrChannels;
	data_size = height * width * channel;

	// TODO: Put this in its own class.
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	image_data = stbi_load("..//Resources//DestertMountainTexture.jpg", &width, &height, &channel, 0);
	if(!image_data)
	{
		std::cout << "ERROR: Failed to load texture" << std::endl;
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glGenerateMipmap(GL_TEXTURE_2D);


	stbi_image_free(image_data);
	image_data = nullptr;
}

void SceneManager::InitFramebuffer()
{
	// TODO: Encapsulate this... This is the setup of a frame buffer object.
	// A frame buffer allows you to draw to a memory buffer instead of a screen buffer.
	
	// Generate Render Buffer.
	glGenRenderbuffers(1, &render_buffer);
	glBindRenderbuffer(GL_RENDERBUFFER, render_buffer);
	glRenderbufferStorage(GL_RENDERBUFFER, PIXEL_FORMAT, screen_width, screen_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind

	// Generate Framebuffer.
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, render_buffer);

	GLenum status = glCheckFramebufferStatus(fbo);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR: Initialising the Framebuffer - " << std::to_string(status) << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // unbind
}

void SceneManager::InitPixelBuffer()
{
	// Create 2x PBOs
	glGenBuffersARB(2, pbo);

	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pbo[0]);
	glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, data_size, 0, GL_STREAM_DRAW_ARB);
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pbo[1]);
	glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, data_size, 0, GL_STREAM_DRAW_ARB);
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	UnpackingPBO();
	
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




void SceneManager::Add(unsigned char * src, int width, int height, int shift, unsigned char * dst)
{
	if(!src || !dst)
		return;

	int value;
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			value = *src + shift;
			if(value > 255) *dst = (unsigned char)255;
			else            *dst = (unsigned char)value;
			++src;
			++dst;

			value = *src + shift;
			if(value > 255) *dst = (unsigned char)255;
			else            *dst = (unsigned char)value;
			++src;
			++dst;

			value = *src + shift;
			if(value > 255) *dst = (unsigned char)255;
			else            *dst = (unsigned char)value;
			++src;
			++dst;

			++src;    // skip alpha
			++dst;
		}
	}
}



void SceneManager::UnpackingPBO()
{
	// "index" is used to read pixels from framebuffer to a PBO
	// "nextIndex" is used to update pixels in the other PBO
	static int index = 0;
	int next_index = 0;

	// This flips the id of the role for each pixel buffer.
	index      = (index + 1) % 2;
	next_index = (index + 1) % 2;

	// Bind the texture and PBO
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pbo[index]);

	// Copy pixels from PBO to texture object.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, 0);

	// bind PBO to update pixel value
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, pbo[next_index]);

	// Map the buffer object into memory
	/// Note that glMapBufferARB() causes sync issues.
	/// If the GPU is working with this buffer, glMapBufferARB() will wait/ stall.
	///	for the GPU to finish its job. To avoid waiting/ stalling, you can call, 
	///	first, glBufferDataARB() with NULL pointer before glMapBufferARB().
	/// If you do that, the previous data in PBO will be discarded and glMapBufferARB()
	///	returns a new allocated pointer immediatly even if the GPU is still working with 
	///	the previous data.
	glBufferDataARB(GL_PIXEL_UNPACK_BUFFER_ARB, data_size, 0, GL_STREAM_DRAW_ARB);
	GLubyte* unpack_src = (GLubyte*)glMapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY_ARB);
	if(unpack_src)
	{
		static int colour = 0;
		if(!unpack_src) return;
		int* unpack_src_ptr = (int*)unpack_src;
		


		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				// TODO: Load texture data from PBO into the texture.
				*unpack_src_ptr = colour;
				unpack_src_ptr++;
			}
			colour += 257;
		}
		colour--;
		glUnmapBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB);
	}
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}


void SceneManager::PackingPBO()
{
	// "index" is used to read pixels from framebuffer to a PBO
	// "nextIndex" is used to update pixels in the other PBO
	static int index = 0;
	int next_index = 0;

	// This flips the id of the role for each pixel buffer.
	index = (index + 1) % 2;
	next_index = (index + 1) % 2;


	/* READ PIXEL DATA FROM SCREEN TO PBO */
	// Normal drawing call to the framebuffer, so the first call of glReadPixels() 
	//	will get valid content.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	models_manager->Draw();

	glRasterPos2i(0, 0);
	glDrawPixels(screen_width, screen_height, PIXEL_FORMAT, GL_UNSIGNED_BYTE, &fbo);

	glutSwapBuffers();


	// bightnes shift
	static int shift = 0;
	shift = ++shift % 200;

	// set the framebuffer to read
	glReadBuffer(GL_FRONT);

	// copy pixels from framebuffer to PBO
	// Use offset instead of pointer.
	// openGL should perform asynch DMA transfer, so glReadPixels() will return immediatly.
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo[index + 2]);
	glReadPixels(0, 0, screen_width, screen_height, PIXEL_FORMAT, GL_UNSIGNED_BYTE, 0);

	// map the pbo that contains framebuffer pixels before processing it. 
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, pbo[next_index + 2]);

	GLubyte* pack_src = (GLubyte*)glMapBufferARB(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
	if(pack_src)
	{
		Add(pack_src, screen_width, screen_height, shift, colour_buffer);
		glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB);     // release pointer to the mapped buffer
	}
	glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
	glDrawBuffer(GL_BACK);
}


void SceneManager::UpdateFramebuffer()
{
	// set rendering destination to FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw a scene to a texture directly
	models_manager->Draw();

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(0, 0, screen_width, screen_height, PIXEL_FORMAT, GL_UNSIGNED_BYTE, 0);

	// unbind FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
