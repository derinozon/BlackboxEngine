#include "material.h"

namespace Blackbox {
	Material::Material () {
		Log("Default Material");
	}

	Material::Material (Shader* shader, Texture* texture) {
		this->shader = shader;
		this->texture = texture;
		Log("Adding Material");
	}

	Material::Material (const char* texturePath) {
		this->shader = nullptr;
		this->texturePath = texturePath;
		this->texture = Resources::LoadTexture(texturePath);
	}

	Material::~Material() {
		Log("Destroying Material");
	}
}