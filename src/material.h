#pragma once

#include "texture.h"
#include "shader.h"

namespace ENG {
	class Material {
	public:
		Material();
		~Material();
		Material(Shader* shader, Texture* texture);
		Material(const char* texturePath);

		std::string texturePath;
		Texture* texture = nullptr;
		Shader* shader = nullptr;
	};
}