#pragma once
#define EDITOR

#ifdef EDITOR
#include "lib/ImGUI/imgui.h"
#include "lib/ImGUI/imgui_impl_glfw.h"
#include "lib/ImGUI/imgui_impl_opengl3.h"
#endif

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
	// #define GL_GLEXT_PROTOTYPES
	// #define EGL_EGLEXT_PROTOTYPES
#endif

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#ifndef __EMSCRIPTEN__
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

#include "src/window.h"
namespace fs = std::filesystem;

const unsigned int width = 1600;
const unsigned int height = 900;

#include "src/debug.h"

#include "serialization.h"
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

namespace ENG {
	inline InputManager& Input = InputManager::Get();
	inline Shader* defaultShader;
	inline Camera camera(1600, 900, glm::vec3(0.0f, 0.0f, 5.0f));

	int run(Window* window);
	Window* init(const char* title, int width = 1600, int height = 900, bool fullscreen = false, bool vsync = true);
	inline Window* currentWindow;
	inline void (*GameLoop)(void);
}