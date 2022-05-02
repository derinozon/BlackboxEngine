#pragma once

#if defined(WIN32) || defined(_WIN32)
#define WIN
#endif

#include "../lib/ImGUI/imgui.h"
#include "../lib/ImGUI/imgui_impl_glfw.h"
#include "../lib/ImGUI/imgui_impl_opengl3.h"

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include <glm/glm.hpp>

#include "window.h"
#include "texture.h"

namespace ENG::Editor {
	ImGuiIO& InitEditor(Window* window);
	void DestroyEditor();
	void Render();
	void NewFrame();
	void Label (const char* label);
	void IntField (const char* label, int* val);
	bool ToggleField (const char* label, bool* val);
	void ImageField(Texture* texture);
	glm::vec3 DragFloat3 (const char* label, glm::vec3 vec, float speed = 0.05);
	glm::vec4 ColorField (const char* label, glm::vec4 color);
}