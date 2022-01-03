#pragma once

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include "mesh.h"

namespace ENG {

	static GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	static GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};


	// Indices for vertices order
	static std::vector<unsigned int> pindices = {
		0, 1, 2,
		2, 0, 3
	};

	static std::vector<Vertex> pvertices = {
		// positions          // colors           // texture coords
		{glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(1.0f, 1.0f)},   // top right
		{glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(1.0f, 0.0f)},   // bottom right
		{glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 0.0f)},   // bottom left
		{glm::vec3(-0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 1.0f)}    // top left 
	};

	// Entity* CreateQuad () {
	// 	Texture* brickTex2 = Resources::Load<Texture>("crate.png");
	// 	Entity* ent = new Entity();
	
	// 	ent->transform = {vec3(0, 0, -10), vec3(0,0,45), vec3(3,3,3)};
	// 	ent->mesh = Mesh(pvertices, pindices);
	// 	ent->material = Material(defaultShader, brickTex2);
	// }


	/*
	// Indices for vertices order
	GLuint pindices[] =
	{
		0, 1, 2,
		2, 0, 3
		// ,
		// 4, 5, 6,
		// 6, 5, 7
	};


	GLfloat pvertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
	}
	*/
}