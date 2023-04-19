#pragma once

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
	#include <emscripten/html5.h>
	#define GL_GLEXT_PROTOTYPES
	#define EGL_EGLEXT_PROTOTYPES
	
	// #include <GL/gl.h>
	// #include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
	#include "include/DG/DG_misc.h"
#endif

#include <GLFW/glfw3.h>

#include "src/window.h"

#include "src/debug.h"

// #include "serialization.h"
#include "src/action.h"
#include "src/gametime.h"
#include "src/texture.h"

// Components //
#include "src/mesh.h"
#include "src/material.h"
#include "src/transform.h"

#include "src/resources.h"
#include "src/shader.h"
#include "src/camera.h"
#include "src/input.h"
#include "src/scene.h"
#include "src/entity.h"
#include "src/primitive.h"
#include "src/model.h"
#include "src/random.h"

namespace Blackbox {
	
	inline InputManager& Input = InputManager::Get();
	inline Shader* defaultShader;
	inline Camera camera(1600, 900, glm::vec3(0.0f, 0.0f, 5.0f));
	inline glm::vec4 clearColor(0.07f, 0.13f, 0.17f, 1.0f);

	int run(Window* window);
	Window* init(const char* title, int width = 1600, int height = 900, bool fullscreen = false, bool vsync = true, bool resizable = true);
	inline Window* currentWindow;
	inline Action OnUpdate = Action();
	inline Action OnDrawGUI = Action();
	inline Action OnQuit = Action();
}