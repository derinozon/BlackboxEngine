#pragma once

#include <glm/glm.hpp>

namespace Blackbox {

	float RandomRange(float min, float max);

	glm::vec3 RandomBox (float boxSize);

	glm::vec4 RandomColor (float brightness = 0.65f);
	
}