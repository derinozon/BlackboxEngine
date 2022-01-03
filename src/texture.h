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
	Texture(const char* image);
	Texture(unsigned char bytes[], int widthImg, int heightImg, int numColCh, GLenum texType);
	Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);
	~Texture();

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
};