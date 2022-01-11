#pragma once

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include "shader.h"

class Texture {
public:
	GLuint ID;
	GLenum type;
	int width, height;

	// Texture(const char* image);
	Texture(unsigned char bytes[], int widthImg, int heightImg, int numColCh, GLenum texType);
	Texture(const char* image, GLenum texType = GL_TEXTURE_2D, GLenum slot = GL_TEXTURE0, GLenum pixelType = GL_UNSIGNED_BYTE);
	~Texture();

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
};