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
		~SceneManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyResize(int width, int height,
								  int previousWidth, int previousHeight);

	private:
		void InitShaders();
		void InitTexture();
		void InitFramebuffer();
		void InitPixelBuffer();
		
		void UpdateFramebuffer();
		
		/**	Copy the Pixel Data onscreen to an ofscreen buffer, and then
				to a Pixel Buffer Object. */
		void PackingPBO();

		/** Copy the Pixel Data in the PBO to the texture on screen. */
		void UnpackingPBO();

		/* Changing the brightness.*/
		void Add(unsigned char* src, int width, int height, int shift, unsigned char* dst);





		GLuint texture;
		GLuint pbo[4];
		GLuint fbo;
		GLuint render_buffer;
		const GLenum PIXEL_FORMAT = GL_BGRA;


		const int nrChannels = 4;

		const int screen_width = 800;
		const int screen_height = 600;
		const int screen_data_size = screen_width * screen_height * nrChannels;

		const int image_width = 1024;
		const int image_height = 1024;
		const int image_data_size = image_width * image_height * nrChannels;

		// aquired from stb
		int width;
		int height;
		int channel;
		int data_size;

		GLubyte* image_data = 0;             // pointer to texture buffer
		GLubyte* colour_buffer = 0;

		std::unique_ptr<Managers::ShaderManager> shader_manager = nullptr;
		std::unique_ptr<Managers::ModelsManager> models_manager = nullptr;
	};
}