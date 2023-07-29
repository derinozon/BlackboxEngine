#pragma once

#include "debug.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace Blackbox {
	class Window {
	public:
		GLFWwindow* Get ();
		glm::vec2 GetSize ();
		void MakeFullscreen ();
		void MakeWindowed ();
		Window (const char* title, int width, int height, bool fullscreen);
		~Window();

	private:
		GLFWwindow* window;
	};
}