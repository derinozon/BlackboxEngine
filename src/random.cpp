#include "random.h"

namespace Blackbox {

	float RandomRange(float min, float max) {
		float random = ((float) rand()) / (float) RAND_MAX;
		float range = max - min;  
		return (random*range) + min;
	}

	glm::vec3 RandomBox (float boxSize) {
		return glm::vec3(
			RandomRange(-1.0, 1.0),
			RandomRange(-1.0, 1.0),
			RandomRange(-1.0, 1.0)
		) * boxSize;
	}

	glm::vec4 RandomColor (float brightness) {
		return glm::vec4(
			RandomRange(brightness, 1.0),
			RandomRange(brightness, 1.0),
			RandomRange(brightness, 1.0),
			1.0
		);
	}
	
}