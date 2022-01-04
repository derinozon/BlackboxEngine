#pragma once

// #include <nlohmann/json.hpp>
#include <glm/glm.hpp>

#include "serialization.h"

namespace ENG {
	struct Transform {
		glm::vec3 position = {0,0,0};
		glm::vec3 rotation = {0,0,0};
		glm::vec3 scale = {1,1,1};

		Transform () {}
		Transform (glm::vec3 pos, glm::vec3 rot, glm::vec3 scl) {
			position = pos;
			rotation = rot;
			scale = scl;
		}

		// NLOHMANN_DEFINE_TYPE_INTRUSIVE(Transform, position, rotation, scale)
	};
}