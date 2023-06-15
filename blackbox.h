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
	#include <DG/DG_misc.h>
#endif

#include <GLFW/glfw3.h>
#include "ECS.h"

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
#include "src/primitive.h"
#include "src/model.h"
#include "src/random.h"

namespace Blackbox {

	class Engine {
		public:
		ECS::World* world;

		InputManager& Input = InputManager::Get();
		Shader* defaultShader;
		Camera camera;
		glm::vec4 clearColor;

		int run(Window* window);
		Window* init(const char* title, int width = 1600, int height = 900, bool fullscreen = false, bool vsync = true, bool resizable = true);
		Window* currentWindow;
		Action OnUpdate = Action();
		Action OnDrawGUI = Action();
		Action OnQuit = Action();

		Engine(){};

		private:
		void loop(void* arg);
	};
}