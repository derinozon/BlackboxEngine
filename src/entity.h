#pragma once

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
	};
}