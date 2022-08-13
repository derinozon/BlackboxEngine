#pragma once

#include "debug.h"

#include <iostream>
#include <GLFW/glfw3.h>

class Window {
public:
	GLFWwindow* Get () {
		return window;
	}

	void MakeFullscreen () {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
 		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}

	void MakeWindowed () {
		GLFWmonitor* monitor = glfwGetWindowMonitor(window);
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
 		glfwSetWindowMonitor(window, NULL, 0, 0, mode->width, mode->height, mode->refreshRate);
	}

	Window (const char* title, int width, int height, bool fullscreen) {
		unsigned int wWidth = width;
		unsigned int wHeight = height;
		#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			// glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
			wWidth = width/2;
			wHeight = height/2;
		#endif
		// Create Window
		window = glfwCreateWindow(
			wWidth, wHeight,
			title,
			fullscreen ? glfwGetPrimaryMonitor() : NULL,
			NULL
		);
		Log("Created window");
	}
	~Window() {
		Log("Destroying Window");
	}

private:
	GLFWwindow* window;
};