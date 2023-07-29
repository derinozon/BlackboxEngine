#pragma once

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include "shader.h"

namespace Blackbox {
	class Texture {
	public:
		GLuint ID;
		GLenum type;
		int width, height, colorChannels;
		
		// Loads texture from memory
		Texture(unsigned char bytes[], int len, int desiredChannels = 4, GLenum texType = GL_TEXTURE_2D);
		Texture(unsigned char bytes[], int widthImg, int heightImg, int numColCh, GLenum texType);
		Texture(const char* image, GLenum texType = GL_TEXTURE_2D);
		~Texture();

		void GetPixelData();
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
	private:
		void GenerateGLTexture(unsigned char data[], GLenum texType = GL_TEXTURE_2D);
	};
}