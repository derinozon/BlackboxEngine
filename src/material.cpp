#include "material.h"
#include "debug.h"

namespace ENG {
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
	}

	Material::~Material() {
		Log("Destroying Material");
	}
}