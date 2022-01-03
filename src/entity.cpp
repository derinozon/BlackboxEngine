#include "entity.h"

namespace ENG {

	Entity::Entity(std::string entityName) {
		name = entityName;
	}

	Entity::Entity() {
		Log("Creating Entity");
	}

	Entity::~Entity() {
		Log("Destroying Entity");
	}

}