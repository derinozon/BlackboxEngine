#pragma once

#include <glm/glm.hpp>

namespace Blackbox {
	struct Transform {
		Transform* parent = nullptr;

		glm::vec3 position = {0,0,0};
		glm::vec3 rotation = {0,0,0};
		glm::vec3 scale = {1,1,1};

		Transform () {}
		Transform (glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
			position = pos;
			rotation = rot;
			scale = scl;
		}
	};
}