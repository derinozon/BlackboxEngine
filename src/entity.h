#pragma once

// #include <nlohmann/json.hpp>

#include "scene.h"
#include "transform.h"
#include "mesh.h"
#include "material.h"
#include "debug.h"

namespace ENG {

	class Entity {
		public:
		std::string name = "DefaultObject";
		Transform transform;
		Mesh mesh;
		Material material;
		Entity();
		Entity(std::string entityName);
		~Entity();

		// NLOHMANN_DEFINE_TYPE_INTRUSIVE(Entity, name, transform, mesh)
	};
}