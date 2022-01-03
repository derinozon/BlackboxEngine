#pragma once

#ifdef __EMSCRIPTEN__
	#include <GL/gl.h>
	#include <GLES3/gl3.h>
#else
	#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"
//#include "gametime.h"

class Camera {
public:
	// Stores the main vectors of the camera
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	bool perspective = false;
	float orthoSize = 10.0f;

	// Stores the width and height of the window
	int width;
	int height;

	float FOV = 60.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void UpdateMatrix();
	// Handles camera inputs
	void Inputs(GLFWwindow* window);
};