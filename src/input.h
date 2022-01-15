#pragma once

#include <GLFW/glfw3.h>

// Legacy Input //
/*
namespace ENG::Input {
	inline bool GetKey(int key) {
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	inline float GetAxisHorizontal () {
		bool left = GetKey(GLFW_KEY_A)||GetKey(GLFW_KEY_LEFT);
		bool right = GetKey(GLFW_KEY_D)||GetKey(GLFW_KEY_RIGHT);
		
		if (left && !right) {
			return -1;
		}
		if (!left && right) {
			return 1;
		}
		
		return 0;
	}

	inline float GetAxisVertical() {
		bool down = GetKey(GLFW_KEY_S)||GetKey(GLFW_KEY_DOWN);
		bool up = GetKey(GLFW_KEY_W)||GetKey(GLFW_KEY_UP);

		if (down && !up) {
			return -1;
		}
		if (!down && up) {
			return 1;
		}

		return 0;
	}
}
*/

namespace ENG {
	class InputManager {
		public:
		// Removes copy constructor
		InputManager(const InputManager&) = delete;

		static InputManager& Get () {
			return instance;
		}

		void SetWindow (GLFWwindow* window) {
			this->window = window;
		}

		bool GetKey(int key) {
			return glfwGetKey(window, key) == GLFW_PRESS;
		}

		bool GetKeyUp (int key) {
			return glfwGetKey(window, key) == GLFW_RELEASE;
		}

		float GetAxisHorizontal () {
			bool left = GetKey(GLFW_KEY_A)||GetKey(GLFW_KEY_LEFT);
			bool right = GetKey(GLFW_KEY_D)||GetKey(GLFW_KEY_RIGHT);
			
			if (left && !right) {
				return -1;
			}
			if (!left && right) {
				return 1;
			}
			return 0;
		}

		float GetAxisVertical() {
			bool down = GetKey(GLFW_KEY_S)||GetKey(GLFW_KEY_DOWN);
			bool up = GetKey(GLFW_KEY_W)||GetKey(GLFW_KEY_UP);

			if (down && !up) {
				return -1;
			}
			if (!down && up) {
				return 1;
			}

			return 0;
		}

		private:
		InputManager () {}

		static InputManager instance;


		GLFWwindow* window;
	};
	inline InputManager InputManager::instance;
}