#include "material.h"

namespace Blackbox {
	Material::Material () {
		LogInternal("Default Material");
	}

	Material::Material (Shader* shader, Texture* texture) {
		this->shader = shader;
		this->texture = texture;
		LogInternal("Adding Material");
	}

	Material::Material (const char* texturePath) {
		this->shader = nullptr;
		this->texturePath = texturePath;
		this->texture = Resources::LoadTexture(texturePath);
	}

	Material::~Material() {
		LogInternal("Destroying Material");
	}
}