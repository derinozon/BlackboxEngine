#pragma once

#include "texture.h"
#include "shader.h"
#include "color.h"
#include "debug.h"
#include "resources.h"

namespace Blackbox {
	struct Material {
		Material();
		~Material();
		Material(Shader* shader, Texture* texture);
		Material(const char* texturePath);

		std::string texturePath;
		Texture* texture = nullptr;
		Shader* shader = nullptr;
		glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		// Color color = {255, 255, 255, 255};
	};
}