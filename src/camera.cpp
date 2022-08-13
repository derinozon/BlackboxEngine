#include "camera.h"


Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::UpdateMatrix() {
	// Initializes matrices since otherwise they will be the null matrix
	
	float deviceRatio = (float)width / height;
	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	if (perspective) {
		projection = glm::perspective(glm::radians(FOV), deviceRatio, nearPlane, farPlane);
	}
	else {
		float xCorrection = width / 1;
		float yCorrection = height / 1;

		float correction = 1<deviceRatio ? yCorrection : xCorrection;
		
		bounds = glm::vec4(
			(-width / 2.0f / correction),  // left
			(width / 2.0f / correction),   // right
			(-height / 2.0f / correction), // bottom
			(height / 2.0f / correction)   // top
		) * orthoSize;

		projection = glm::ortho(bounds.x, bounds.y, bounds.z, bounds.w, nearPlane, farPlane);
	}
}

void Camera::Inputs(GLFWwindow* window)
{
	
}