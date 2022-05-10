#pragma once

// #ifdef __EMSCRIPTEN__
// 	#include <GL/gl.h>
// 	#include <GLES3/gl3.h>
// #else
// 	#include <glad/glad.h>
// #endif

#include "mesh.h"
#include "entity.h"

namespace Blackbox {
	/*
	static GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	static GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};
	*/

	

	Entity* CreateQuad (const char* label);
	Entity* CreateQuad ();
}