#include "camera.h"


Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::UpdateMatrix() {
	// Initializes matrices since otherwise they will be the null matrix
	

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	if (perspective) {
		projection = glm::perspective(glm::radians(FOV), (float)width / height, nearPlane, farPlane);
	}
	else {
		float correction;
		float deviceRatio = width / height;
		float virtualRatio = 1;
		float xCorrection = width / 1;
		float yCorrection = height / 1;

		if (virtualRatio < deviceRatio) {
		correction = yCorrection;
		} else {
		correction = xCorrection;
		}
		
		float left = (-width / 2.0f / correction) * orthoSize;
		float right = (width / 2.0f / correction) * orthoSize;
		float bottom = (-height / 2.0f / correction) * orthoSize;
		float top = (height / 2.0f / correction) * orthoSize;

		// Now set matrix which includes correction.
		projection = glm::ortho(left, right, bottom, top);
	}
}

void Camera::Inputs(GLFWwindow* window)
{
	
}